# miniRT - Ray Tracer

A simple ray tracer implementation in C using the miniLibX library.

## 🚀 Quick Start

### Compilation
```bash
make
```

### Running
```bash
# Test with a valid scene
./miniRT scenes/valid/test_simple.rt

# Test validation with invalid scene
./miniRT scenes/invalid/test_invalid_colors.rt
```

## 📁 Project Structure

```
ray-trace/
├── src/                    # Source code
│   ├── parser/            # Scene file parsing
│   ├── world/             # World and lighting
│   ├── computation/       # Ray-object intersection
│   ├── camera/            # Camera and rendering
│   └── ...               # Other modules
├── includes/              # Header files
├── scenes/                # Test scenes
│   ├── valid/            # Valid scene files
│   ├── invalid/          # Invalid scene files (for testing validation)
│   └── README.md         # Scene documentation
├── tests/                 # Unit tests
└── utils/                 # Utilities and libraries
```

## 🎯 Testing

### Automated Testing
Use the provided test script to validate all scenes:

```bash
# Test all scenes
./test_scenes.sh

# Test only valid scenes
./test_scenes.sh valid

# Test only invalid scenes
./test_scenes.sh invalid

# Show detailed error messages
./test_scenes.sh errors
```

### Manual Testing
```bash
# Valid scenes (should render)
./miniRT scenes/valid/green_blue_spheres.rt
./miniRT scenes/valid/multiple_spheres_with_patterns.rt
./miniRT scenes/valid/zeze_ambient.rt

# Invalid scenes (should show validation errors)
./miniRT scenes/invalid/test_invalid_colors.rt
./miniRT scenes/invalid/test_missing_params.rt
```

## 🔧 Features

### Scene Elements
- **Ambient Light**: Global illumination
- **Camera**: Perspective projection with configurable FOV
- **Point Lights**: Positioned light sources
- **Spheres**: Basic sphere primitives
- **Cylinders**: Cylindrical objects

### Rendering Features
- Phong lighting model
- Shadow calculation
- Specular reflection
- Multiple light sources
- Anti-aliasing (shadow acne prevention)

### Parser Validation
- RGB color validation (0-255 range)
- Parameter count validation
- Range validation for ratios, FOV, dimensions
- Comprehensive error messages
- Graceful error handling

## 🐛 Recent Fixes

### Shadow Acne Fix
- Added separate `SHADOW_EPSILON` constant for shadow calculations
- Modified `prepare_computations()` to use appropriate epsilon for over_point
- Updated `is_shadowed()` function thresholds
- Prevents self-intersection artifacts on distant objects

### Parser Improvements
- Robust validation system for all scene elements
- Clear error messages for debugging
- Prevention of buffer overflows
- Support for multiple validation rules per element

## 📝 Scene File Format

```
A 0.2 255,255,255                     # Ambient light
C 0,0,-3 0,0,1 70                     # Camera
L -10,10,-10 0.7 255,255,255          # Point light
sp 0,0,5 3 255,0,0                    # Sphere
cy 0,0,5 0,1,0 2 5 0,255,0            # Cylinder
```

## 🎨 Examples

See `scenes/valid/` for working examples and `scenes/invalid/` for validation test cases.

## 📜 License

This project is part of the 42 School curriculum.
