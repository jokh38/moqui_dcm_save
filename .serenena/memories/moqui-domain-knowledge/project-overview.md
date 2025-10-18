# Moqui Domain Project Overview

## Project Identity

**Project Name**: moqui_dcm_save
**Project Type**: moqui-domain
**AI Context**: monte-carlo-physics
**Primary Focus**: Monte Carlo dose calculation for radiotherapy
**Domain**: Medical Physics, Computational Science

## Core Architecture

### Monte Carlo Engine
- **Location**: `moqui/base/`
- **Purpose**: Physics simulation for particle transport
- **Key Components**:
  - Particle transport algorithms
  - Energy deposition calculations
  - Material interaction modeling
  - Scoring systems for dose calculation

### DICOM Integration
- **Purpose**: Medical imaging data processing
- **Capabilities**:
  - CT image import and processing
  - Hounsfield unit conversion
  - Patient geometry reconstruction
  - Treatment planning data integration

### Treatment Machine Models
- **Location**: `moqui/treatment_machines/`
- **Purpose**: Radiotherapy equipment simulation
- **Features**:
  - Beam source modeling
  - Machine-specific geometry
  - Beam modulation devices
  - Accurate machine parameter representation

## Physics Capabilities

### Supported Particle Types
- Protons
- Heavy ions (carbon, helium, etc.)
- Photons
- Electrons

### Physics Processes
- Elastic scattering
- Inelastic scattering
- Ionization
- Nuclear interactions
- Multiple scattering
- Energy loss calculations

### Treatment Techniques
- Pencil beam scanning (PBS)
- Passive scattering
- Intensity modulated radiotherapy (IMRT)
- Volumetric modulated arc therapy (VMAT)

## Code Standards and Practices

### C++ Standards
- **Standard**: C++17
- **Naming**: `mqi_` prefix for all public symbols
- **Memory Management**: RAII principles
- **Error Handling**: Comprehensive error checking
- **Performance**: Optimized for computational efficiency

### Mathematical Rigor
- All physics algorithms mathematically validated
- Numerical stability prioritized
- Precision maintained throughout calculations
- Cross-validation with reference implementations

## Development Environment

### Build System
- **Primary**: CMake
- **Compiler**: GCC, Clang, MSVC support
- **Testing**: GoogleTest framework
- **Code Quality**: clang-format, clang-tidy

### Dependencies
- Physics libraries for computational methods
- DICOM libraries for medical imaging
- Mathematical libraries for numerical methods
- Threading libraries for parallel computation

## Validation and Quality Assurance

### Physics Validation
- Comparison with reference implementations
- Experimental data validation where available
- Cross-validation with established Monte Carlo codes
- Comprehensive documentation of validation results

### Code Quality
- Unit test coverage for all physics functions
- Integration tests for complete workflows
- Performance regression testing
- Static analysis and code review

## Performance Characteristics

### Computational Performance
- Optimized for large-scale Monte Carlo simulations
- Parallel processing capabilities
- Memory-efficient algorithms
- Fast particle transport implementations

### Accuracy
- Sub-millimeter spatial accuracy
- Dose calculation accuracy within clinical requirements
- Robust numerical algorithms
- High-precision floating-point operations

## Regulatory and Safety Considerations

### Medical Device Standards
- Code follows medical device software standards
- Comprehensive documentation for regulatory compliance
- Traceability for safety-critical components
- Version control and change management procedures

### Data Privacy
- HIPAA compliance for patient data
- Secure handling of medical information
- Patient data anonymization in testing
- DICOM confidentiality standards adherence

## Known Limitations and Constraints

### Computational Constraints
- High computational requirements for large simulations
- Memory usage for detailed patient models
- Processing time for complex treatment plans

### Physics Constraints
- Limited to established physics models
- Accuracy dependent on input data quality
- Computational approximations in complex geometries

## Integration Points

### External Systems
- DICOM-compliant treatment planning systems
- Medical imaging platforms
- Treatment machine control systems
- Quality assurance systems

### Data Formats
- DICOM RT (Radiotherapy) formats
- Various CT image formats
- Treatment planning system exports
- Quality assurance measurement data

## Future Development Directions

### Physics Enhancements
- Additional particle types
- Improved physics models
- Enhanced biological modeling
- Faster algorithms

### System Integration
- Enhanced DICOM compatibility
- Treatment planning system integration
- Real-time calculation capabilities
- Cloud computing integration

## Maintenance and Support

### Code Maintenance
- Regular updates to physics models
- Performance optimization
- Bug fixes and improvements
- Documentation updates

### User Support
- Technical documentation
- User training materials
- Troubleshooting guides
- Community support channels

This memory provides comprehensive context for the Moqui domain project, enabling AI assistants to understand the project's scope, requirements, and constraints when providing development assistance.
