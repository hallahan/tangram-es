#include "osmXmlSource.h"
#include "util/mapProjection.h"

#include "tileData.h"
#include "tile/tile.h"
#include "tile/tileID.h"
#include "tile/tileTask.h"
#include "util/geoJson.h"
#include "platform.h"

#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;

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

    xml_document<> doc;
    xml_node<> * root_node;

    // Parse data into an XML document
    // const char* error;
    // size_t offset;
    // const char* rawTileData = task.rawTileData->data();
    // auto document = JsonParseBytes(rawTileData, task.rawTileData->size(), &error, &offset);

    // if (error) {
    //     LOGE("Json parsing failed on tile [%s]: %s (%u)", task.tileId().toString().c_str(), error, offset);
    //     return tileData;
    // }

    return tileData;

}

void OsmXmlSource::constructURL(const TileID& _tileCoord, std::string& _url) const {
    _url.assign(m_urlTemplate);
    BoundingBox tileBounds = m_scene.mapProjection()->TileLonLatBounds(_tileCoord);
    try {
        size_t lpos = _url.find("{l}");
        _url.replace(lpos, 3, std::to_string(tileBounds.min.x));
        size_t bpos = _url.find("{b}");
        _url.replace(bpos, 3, std::to_string(tileBounds.min.y));
        size_t rpos = _url.find("{r}");
        _url.replace(rpos, 3, std::to_string(tileBounds.max.x));
        size_t tpos = _url.find("{t}");
        _url.replace(tpos, 3, std::to_string(tileBounds.min.y));
    } catch(...) {
        LOGE("Bad URL template!");
    }
}

}