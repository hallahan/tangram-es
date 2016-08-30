#pragma once

#include "dataSource.h"
#include "scene/scene.h"

namespace Tangram {
    
class OsmXmlSource: public DataSource {
        
protected:
        
    virtual std::shared_ptr<TileData> parse(const TileTask& _task,
                                            const MapProjection& _projection) const override;

    void constructURL(const TileID& _tileCoord, std::string& _url) const override;

    std::shared_ptr<Scene> m_scene;

public:
        
    OsmXmlSource(const std::string& _name, const std::string& _urlTemplate, int32_t _minZoom, int32_t _maxZoom,
                 const std::shared_ptr<Scene> _scene);
        
};
    
}
