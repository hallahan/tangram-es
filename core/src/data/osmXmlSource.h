#ifndef osmXmlSource_h
#define osmXmlSource_h

#include "dataSource.h"
#include "scene/scene.h"

namespace Tangram {
    
class OsmXmlSource: public DataSource {
        
protected:
        
    virtual std::shared_ptr<TileData> parse(const TileTask& _task,
                                            const MapProjection& _projection) const override;

    void constructURL(const TileID& _tileCoord, std::string& _url) const override;

    Scene m_scene;
    
public:
        
    OsmXmlSource(const std::string& _name, const std::string& _urlTemplate, int32_t _maxZoom,
                 const Scene& _scene);
        
};
    
}


#endif /* osmXmlSource_h */