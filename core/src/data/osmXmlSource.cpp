#include "osmXmlSource.h"
#include "util/mapProjection.h"

#include "tileData.h"
#include "tile/tile.h"
#include "tile/tileID.h"
#include "tile/tileTask.h"
#include "util/geoJson.h"
#include "osm/memoryDataSet.h"
#include "osm/xmlParser.h"
#include "platform.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

namespace Tangram {

OsmXmlSource::OsmXmlSource(const std::string& _name, const std::string& _urlTemplate, 
                           int32_t _maxZoom, const std::shared_ptr<Scene> _scene) :
    DataSource(_name, _urlTemplate, _maxZoom), m_scene(_scene) {
}

std::shared_ptr<TileData> OsmXmlSource::parse(const TileTask& _task,
                                               const MapProjection& _projection) const {

    auto& task = static_cast<const DownloadTileTask&>(_task);

    std::shared_ptr<TileData> tileData = std::make_shared<TileData>();
    
    std::shared_ptr<OSM::MemoryDataSet> memoryDataSet = std::make_shared<OSM::MemoryDataSet>();
    OSM::XmlParser xmlParser(memoryDataSet);
    auto rawTileData = task.rawTileData;
    xmlParser.parse(rawTileData->data(), rawTileData->size());

    LOGN("OSM XML Tile: %s - %zu elements", task.tileId().toString().c_str(), memoryDataSet->size());

    BoundingBox tileBounds(_projection.TileBounds(task.tileId()));
    glm::dvec2 tileOrigin = {tileBounds.min.x, tileBounds.max.y*-1.0};
    double tileInverseScale = 1.0 / tileBounds.width();

    const auto projFn = [&](glm::dvec2 _lonLat){
        glm::dvec2 tmp = _projection.LonLatToMeters(_lonLat);
        return Point {
            (tmp.x - tileOrigin.x) * tileInverseScale,
            (tmp.y - tileOrigin.y) * tileInverseScale,
             0
        };
    };

    tileData->layers.push_back(memoryDataSet->getLayer(projFn, m_id));

    LOGN("SQLite3 version: %s", SQLite::VERSION);
    LOGN("SQLiteC++ version: %s", SQLITECPP_VERSION);
    SQLite::Database db("/Users/njh/code/tangram-es/external/SQLiteCpp/examples/example1/example.db3");
//    db.execAndGet("CREATE TABLE IF NOT EXISTS test(col1 TEXT, col2 TEXT);");
//    db.execAndGet("INSERT OR REPLACE INTO test VALUES ('test1', 'test2');");
//    const char* value = db.execAndGet("SELECT col1 FROM test WHERE col2='test2'");
//    LOGN("Selected value from db: %s", value);

    // Test if the 'test' table exists
    const bool bExists = db.tableExists("test");
    LOGN("SQLite table 'test' exists= %b", bExists);

    // Get a single value result with an easy to use shortcut
    const std::string value = db.execAndGet("SELECT value FROM test WHERE id=2");
    LOGN("execAndGet= %s", value.c_str());

    return tileData;

}

void OsmXmlSource::constructURL(const TileID& _tileCoord, std::string& _url) const {
    _url.assign(m_urlTemplate);
    BoundingBox tileBounds = m_scene->mapProjection()->TileLonLatBounds(_tileCoord);
    // Something is funky about what we're getting from TileLonLatBounds,
    // but this works... (I'm guessing it's thinking in TMS rathar Google Tiles?)
    double l = tileBounds.min.x;
    double b = - tileBounds.max.y;
    double r = tileBounds.max.x;
    double t = - tileBounds.min.y;
    
    try {
        size_t lpos = _url.find("{l}");
        _url.replace(lpos, 3, std::to_string(l));
        size_t bpos = _url.find("{b}");
        _url.replace(bpos, 3, std::to_string(b));
        size_t rpos = _url.find("{r}");
        _url.replace(rpos, 3, std::to_string(r));
        size_t tpos = _url.find("{t}");
        _url.replace(tpos, 3, std::to_string(t));
    } catch(...) {
        LOGE("Bad URL template!");
    }
}

}