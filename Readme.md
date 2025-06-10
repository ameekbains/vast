# VAST

VAST is a GPU accelerated tool for video artifact detection. It uses Qt 6 for
its interface and FFmpeg for video decoding. Plugins can extend the detection
capabilities at runtime.

## Building

```
mkdir build && cd build
cmake ..
make
```

Qt 6 and FFmpeg development packages are required for building. CUDA is
optional and used only for GPU accelerated detectors. Pass
`-DVAST_ENABLE_CUDA=OFF` to `cmake` to build without CUDA.

### Packaging

To generate a portable archive with all binaries run:

```
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target package
```

The resulting archive under `build/` contains the application and the example
detector plugin in `plugins/`.

At runtime VAST loads all libraries from a `plugins/` directory located next to
the executable.

### Plugin API

Plugins are shared libraries that export a `createDetector` function returning
an instance of `ArtifactDetector`.

```
extern "C" ArtifactDetector* createDetector();
```

The shared library is placed in the `plugins/` directory next to the
executable.

### Running Tests

From the `build/` directory run:

```
ctest --output-on-failure
```
