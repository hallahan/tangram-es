#pragma once

#include "data/properties.h"
#include "util/ease.h"
#include <array>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

namespace Tangram {

class DataSource;
class InputHandler;
class Labels;
class Scene;
class TileManager;
class TileWorker;
class View;

struct TouchItem {
    std::shared_ptr<Properties> properties;
    float position[2];
    float distance;
};

class Map {

public:

    // Create resources and initialize the map view using the scene file at the
    // given resource path
    Map(const char* _scenePath);

    ~Map();

    // Load the scene at the given absolute file path
    void loadScene(const char* _scenePath);

    // Request an update to the scene configuration; the path is a series of yaml keys
    // separated by a '.' and the value is a string of yaml to replace the current value
    // at the given path in the scene
    void queueSceneUpdate(const char* _path, const char* _value);

    // Apply all previously requested scene updates
    void applySceneUpdates();

    // Initialize graphics resources; OpenGL context must be created prior to calling this
    void setupGL();

    // Resize the map view to a new width and height (in pixels)
    void resize(int _newWidth, int _newHeight);

    // Update the map state with the time interval since the last update, returns
    // true when the current view is completely loaded (all tiles are available and
    // no animation in progress)
    bool update(float _dt);

    // Render a new frame of the map view (if needed)
    void render();

    // Set the position of the map view in degrees longitude and latitude; if duration
    // (in seconds) is provided, position eases to the set value over the duration;
    // calling either version of the setter overrides all previous calls
    void setPosition(double _lon, double _lat);
    void setPositionEased(double _lon, double _lat, float _duration, EaseType _e = EaseType::quint);

    // Set the values of the arguments to the position of the map view in degrees
    // longitude and latitude
    void getPosition(double& _lon, double& _lat);

    // Set the fractional zoom level of the view; if duration (in seconds) is provided,
    // zoom eases to the set value over the duration; calling either version of the setter
    // overrides all previous calls
    void setZoom(float _z);
    void setZoomEased(float _z, float _duration, EaseType _e = EaseType::quint);

    // Get the fractional zoom level of the view
    float getZoom();

    // Set the counter-clockwise rotation of the view in radians; 0 corresponds to
    // North pointing up; if duration (in seconds) is provided, rotation eases to the
    // the set value over the duration; calling either version of the setter overrides
    // all previous calls
    void setRotation(float _radians);
    void setRotationEased(float _radians, float _duration, EaseType _e = EaseType::quint);

    // Get the counter-clockwise rotation of the view in radians; 0 corresponds to
    // North pointing up
    float getRotation();

    // Set the tilt angle of the view in radians; 0 corresponds to straight down;
    // if duration (in seconds) is provided, tilt eases to the set value over the
    // duration; calling either version of the setter overrides all previous calls
    void setTilt(float _radians);
    void setTiltEased(float _radians, float _duration, EaseType _e = EaseType::quint);

    // Get the tilt angle of the view in radians; 0 corresponds to straight down
    float getTilt();

    // Set the camera type (0 = perspective, 1 = isometric, 2 = flat)
    void setCameraType(int _type);

    // Get the camera type (0 = perspective, 1 = isometric, 2 = flat)
    int getCameraType();

    // Transform coordinates in screen space (x right, y down) into their longitude
    // and latitude in the map view
    void screenToWorldCoordinates(double& _x, double& _y);

    // Set the ratio of hardware pixels to logical pixels (defaults to 1.0)
    void setPixelScale(float _pixelsPerPoint);

    // Add a data source for adding drawable map data, which will be styled
    // according to the scene file using the provided data source name;
    void addDataSource(std::shared_ptr<DataSource> _source);

    // Remove a data source from the map; returns true if the source was found
    // and removed, otherwise returns false.
    bool removeDataSource(DataSource& _source);

    void clearDataSource(DataSource& _source, bool _data, bool _tiles);

    // Respond to a tap at the given screen coordinates (x right, y down)
    void handleTapGesture(float _posX, float _posY);

    // Respond to a double tap at the given screen coordinates (x right, y down)
    void handleDoubleTapGesture(float _posX, float _posY);

    // Respond to a drag with the given displacement in screen coordinates (x right, y down)
    void handlePanGesture(float _startX, float _startY, float _endX, float _endY);

    // Respond to a fling from the given position with the given velocity in screen coordinates
    void handleFlingGesture(float _posX, float _posY, float _velocityX, float _velocityY);

    // Respond to a pinch at the given position in screen coordinates with the given
    // incremental scale
    void handlePinchGesture(float _posX, float _posY, float _scale, float _velocity);

    // Respond to a rotation gesture with the given incremental rotation in radians
    void handleRotateGesture(float _posX, float _posY, float _rotation);

    // Respond to a two-finger shove with the given distance in screen coordinates
    void handleShoveGesture(float _distance);

    // Set whether the OpenGL state will be cached between subsequent frames; this improves rendering
    // efficiency, but can cause errors if your application code makes OpenGL calls (false by default)
    void useCachedGlState(bool _use);

    const std::vector<TouchItem>& pickFeaturesAt(float _x, float _y);

private:

    enum class EaseField { position, zoom, rotation, tilt };

    void setEase(EaseField _f, Ease _e);
    void clearEase(EaseField _f);
    void setScene(std::shared_ptr<Scene>& _scene);
    void setPositionNow(double _lon, double _lat);
    void setZoomNow(float _z);
    void setRotationNow(float _radians);
    void setTiltNow(float _radians);

    std::mutex m_tilesMutex;
    std::unique_ptr<TileWorker> m_tileWorker;
    std::unique_ptr<TileManager> m_tileManager;
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<View> m_view;
    std::unique_ptr<Labels> m_labels;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::array<Ease, 4> m_eases;
    bool m_cacheGlState;

};

void runOnMainLoop(std::function<void()> _task);

float frameTime();

enum DebugFlags {
    freeze_tiles = 0,   // While on, the set of tiles currently being drawn will not update to match the view
    proxy_colors,       // Applies a color change to every other zoom level of tiles to visualize proxy tile behavior
    tile_bounds,        // Draws tile boundaries
    tile_infos,         // Debug tile infos
    labels,             // Debug label bounding boxes
    tangram_infos,      // Various text tangram debug info printed on the screen
    all_labels,         // Draw all labels
    tangram_stats,      // Tangram frame graph stats
};

// Set debug features on or off using a boolean (see debug.h)
void setDebugFlag(DebugFlags _flag, bool _on);

// Get the boolean state of a debug feature (see debug.h)
bool getDebugFlag(DebugFlags _flag);

// Toggle the boolean state of a debug feature (see debug.h)
void toggleDebugFlag(DebugFlags _flag);

}

