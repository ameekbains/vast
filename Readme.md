# VAST

VAST (Video Analysis & Streaming Toolkit) aims to be a cross-platform open source application for processing and streaming video with modern GPU acceleration. The project is in early stages but will ultimately let users build rich video workflows through a plugin-based architecture.

## Features

- **Flexible video pipeline** with playback, transformation, and output plugins
- **Qt 6.x GUI** for cross-platform user interfaces
- **FFmpeg integration** for reading and encoding numerous video formats
- **OpenCL acceleration** to take advantage of GPUs

## Installation

### Dependencies

- **Qt 6.x** for GUI components
- **FFmpeg** command line tools (`ffmpeg`, `ffprobe`)
- **OpenCL** runtime libraries and headers

On Debian or Ubuntu you can install dependencies with:

```bash
sudo apt install qt6-base-dev ffmpeg ocl-icd-opencl-dev
```

### Build

The project currently builds using CMake. From the repository root:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

After building, run the main executable:

```bash
./vast --help
```

This prints the available command line options and will load plugins from the default directory.

## Architecture overview

VAST is planned around a plugin-driven pipeline. Each stage of the video processing chain—input, filters, effects, outputs—is implemented as a plugin that is loaded at runtime. Plugins communicate using shared data structures and can be developed independently of the core.

```
[Input Plugin] -> [Filter Plugins] -> [Output Plugin]
```

Plugin binaries live in the `plugins/` directory and are discovered when VAST starts. A simple plugin API exposes hooks for initialization and frame processing. Plugins can be written in C++ and compiled as shared libraries.

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to propose patches and report issues.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for more information.

