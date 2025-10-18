# Moqui Domain AI Context

## Project Overview

This is the **Moqui Domain** context for AI-assisted development of the Monte Carlo dose calculation system. This context should only be used when working on the Moqui-specific components in the `moqui/` directory.

## Project Type

- **Type**: `moqui-domain`
- **AI Context**: `monte-carlo-physics`
- **Primary Language**: C++
- **Build System**: CMake
- **Domain**: Medical Physics, Radiotherapy, Monte Carlo Simulation

## Core Components

### Monte Carlo Engine
- **Location**: `moqui/base/`
- **Purpose**: Physics simulation engine for particle transport
- **Key Features**:
  - Particle transport simulation
  - Energy deposition calculations
  - Multiple particle types (protons, ions, photons, electrons)
  - Material interaction modeling
  - Dose calculation algorithms

### DICOM Integration
- **Location**: `moqui/base/mqi_ct.hpp`, various DICOM handlers
- **Purpose**: Medical imaging data processing
- **Key Features**:
  - CT image import and processing
  - Hounsfield unit to material density conversion
  - Patient geometry reconstruction
  - Treatment planning data import

### Treatment Machine Models
- **Location**: `moqui/treatment_machines/`
- **Purpose**: Radiotherapy equipment modeling
- **Key Features**:
  - Beam source modeling
  - Treatment machine geometry
  - Beam modulation devices
  - Machine-specific parameters

### Physics Processes
- **Location**: `moqui/base/` (various physics files)
- **Purpose**: Particle interaction modeling
- **Key Features**:
  - Elastic and inelastic scattering
  - Ionization processes
  - Nuclear interactions
  - Energy loss calculations

## Development Guidelines

### Code Standards
- **C++ Standard**: C++17
- **Naming Convention**: `mqi_` prefix for all public symbols
- **Memory Management**: RAII principles, smart pointers where appropriate
- **Error Handling**: Robust error checking with clear error messages
- **Performance**: Optimized for computational physics workloads

### Testing Strategy
- **Unit Tests**: Test individual physics functions and algorithms
- **Integration Tests**: Test complete beam transport and dose calculation
- **Validation**: Compare results with reference implementations
- **Performance Tests**: Benchmark computational performance

### Documentation Requirements
- **Code Comments**: Physics algorithms need detailed mathematical comments
- **API Documentation**: Clear documentation of function parameters and units
- **Physics Validation**: Document validation results against reference data
- **Performance Notes**: Document computational complexity and optimizations

## Key Architectural Invariants

1. **Physics Accuracy**: Never compromise physics accuracy for performance
2. **Numerical Stability**: Ensure numerical stability in all calculations
3. **Memory Efficiency**: Optimize memory usage for large-scale simulations
4. **Thread Safety**: Design for parallel computation where applicable
5. **Reproducibility**: Ensure deterministic results across platforms

## Common Tasks

### Adding New Physics Processes
1. Implement physics process class in `moqui/base/`
2. Add process to physics list in `mqi_physics_list.hpp`
3. Create unit tests for the new process
4. Validate against reference data
5. Update documentation

### Integrating New Treatment Machines
1. Create machine model in `moqui/treatment_machines/`
2. Implement machine-specific parameters
3. Add to machine factory
4. Test with standard beam configurations
5. Update machine database

### DICOM Format Support
1. Add DICOM parser for new format
2. Implement data conversion functions
3. Test with sample DICOM files
4. Validate data integrity
5. Update import/export capabilities

## Tools and Dependencies

### Required Tools
- **CMake**: Build system
- **clang-format/clang-tidy**: Code formatting and static analysis
- **GoogleTest**: Testing framework
- **Git**: Version control
- **Serena MCP**: AI development assistant

### External Dependencies
- **Physics Libraries**: Various computational physics libraries
- **DICOM Libraries**: Medical imaging format support
- **Math Libraries**: Linear algebra and numerical methods

## Performance Considerations

### Optimization Priorities
1. **Monte Carlo Simulation Speed**: Primary performance metric
2. **Memory Usage**: Large patient datasets and particle histories
3. **Parallel Scaling**: Multi-threading and SIMD optimizations
4. **Numerical Accuracy**: Maintain precision while optimizing speed

### Profiling Guidelines
- Profile complete simulation workflows
- Focus on hot paths in particle transport
- Monitor memory allocation patterns
- Validate that optimizations don't affect physics accuracy

## Validation and Quality Assurance

### Physics Validation
- Compare with reference implementations
- Validate against experimental data where available
- Cross-validate with other Monte Carlo codes
- Document validation results thoroughly

### Code Quality
- Comprehensive unit test coverage
- Integration tests for complete workflows
- Static analysis and code review
- Performance regression testing

## Serena MCP Integration

### Context Usage
- Use this context when working on Moqui-specific code
- Serena should have access to physics domain knowledge
- Memory system contains Moqui-specific information
- Context switching required for template work

### Common AI Tasks
- Physics algorithm optimization
- Code refactoring while preserving accuracy
- Test generation for physics functions
- Documentation enhancement
- Performance analysis and optimization

## Security and Compliance

### Medical Device Considerations
- Code follows medical device software standards
- Traceability for safety-critical components
- Validation documentation for regulatory compliance
- Version control and change management

### Data Privacy
- Handle patient data according to healthcare regulations
- Implement secure data handling practices
- Ensure anonymization of patient information in testing
- Follow DICOM confidentiality standards

## Related Files and Contexts

- **Template Context**: Use `github/claude/contexts/cpp-template.md` for generic C++ work
- **Shared Context**: Use `github/claude/contexts/shared-workflows.md` for common development tasks
- **Domain Knowledge**: Available in `.serena/memories/moqui-domain-knowledge/`

## Contact and Support

- **Project Repository**: Main development repository
- **Documentation**: Technical documentation and API references
- **Issue Tracking**: Bug reports and feature requests
- **AI Assistant**: Serena MCP with this context enabled
