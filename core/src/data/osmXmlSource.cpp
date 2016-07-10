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

namespace Tangram {

OsmXmlSource::OsmXmlSource(const std::string& _name, const std::string& _urlTemplate, 
                           int32_t _maxZoom, const Scene& _scene) :
    DataSource(_name, _urlTemplate, _maxZoom), m_scene(_scene) {
}

std::shared_ptr<TileData> OsmXmlSource::parse(const TileTask& _task,
                                               const MapProjection& _projection) const {

    auto& task = static_cast<const DownloadTileTask&>(_task);
    LOGN("OSM XML Tile: %s", task.tileId().toString().c_str());

    std::shared_ptr<TileData> tileData = std::make_shared<TileData>();
    
    std::shared_ptr<OSM::MemoryDataSet> memoryDataSet = std::make_shared<OSM::MemoryDataSet>();
    OSM::XmlParser xmlParser(memoryDataSet);
    xmlParser.parse(task.rawTileData->data());

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

    return tileData;

}

void OsmXmlSource::constructURL(const TileID& _tileCoord, std::string& _url) const {
    _url.assign(m_urlTemplate);
    BoundingBox tileBounds = m_scene.mapProjection()->TileLonLatBounds(_tileCoord);
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