#ifndef osmXmlSource_h
#define osmXmlSource_h

#include "dataSource.h"

namespace Tangram {
    
class OsmXmlSource: public DataSource {
        
protected:
        
    virtual std::shared_ptr<TileData> parse(const TileTask& _task,
                                            const MapProjection& _projection) const override;
        
public:
        
    OsmXmlSource(const std::string& _name, const std::string& _urlTemplate, int32_t _maxZoom);
        
};
    
}


#endif /* osmXmlSource_h */