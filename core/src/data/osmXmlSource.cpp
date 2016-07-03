#include "osmXmlSource.h"
#include "util/mapProjection.h"

#include "tileData.h"
#include "tile/tile.h"
#include "tile/tileID.h"
#include "tile/tileTask.h"
#include "util/geoJson.h"
#include "platform.h"

namespace Tangram {

OsmXmlSource::OsmXmlSource(const std::string& _name, const std::string& _urlTemplate, int32_t _maxZoom) :
    DataSource(_name, _urlTemplate, _maxZoom) {
}

std::shared_ptr<TileData> OsmXmlSource::parse(const TileTask& _task,
                                               const MapProjection& _projection) const {

    auto& task = static_cast<const DownloadTileTask&>(_task);
    LOGN("OSM XML Tile: %s", task.tileId().toString().c_str());

    std::shared_ptr<TileData> tileData = std::make_shared<TileData>();

    return tileData;

}

}