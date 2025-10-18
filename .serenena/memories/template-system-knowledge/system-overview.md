# CICD Template System Overview

## System Purpose

The CICD Template System transforms the moqui_dcm_save project into a **dual-purpose system** that:
1. Preserves world-class Monte Carlo dose calculation capabilities
2. Provides generic project templates for AI-enhanced development workflows
3. Maintains clean separation between domain-specific and generic code
4. Enables rapid project setup with modern development tools

## Architecture Overview

### Directory Structure
```
moqui_dcm_save/
├── moqui/                    # Moqui domain (Monte Carlo engine)
├── templates/                # Generic project templates
│   ├── base-cpp/            # C++ project template
│   └── base-python/         # Python project template
├── scripts/                 # Template system scripts
│   ├── detect-project-type.sh
│   └── validate-template.sh
├── setup-scripts/           # Development environment setup
├── git-hooks/              # Enhanced git hooks
├── .github/claude/contexts/ # AI context separation
└── .serena/memories/       # AI memory system
```

### Core Components

#### 1. Project Type Detection System
- **Script**: `scripts/detect-project-type.sh`
- **Purpose**: Automatically identifies project type and sets AI context
- **Supported Types**:
  - `moqui-domain`: Monte Carlo physics simulation
  - `python-template`: Generic Python projects
  - `cpp-template`: Generic C++ projects
  - `dual-system`: Repository containing both systems

#### 2. Template Validation System
- **Script**: `scripts/validate-template.sh`
- **Purpose**: Prevents domain code contamination in templates
- **Features**:
  - Automated contamination detection
  - Domain-specific term checking
  - Template structure validation
  - Continuous monitoring capabilities

#### 3. AI Context Separation
- **Location**: `.github/claude/contexts/`
- **Contexts**:
  - `moqui-domain.md`: Monte Carlo physics context
  - `cpp-template.md`: Generic C++ project context
  - `python-template.md`: Generic Python project context
  - `shared-workflows.md`: Common development workflows

#### 4. Template System
- **Base Templates**: `templates/base-cpp/`, `templates/base-python/`
- **Generation**: Cookiecutter-based project generation
- **Features**:
  - Modern development tools integration
  - AI workflow templates
  - Automated quality checks
  - Cross-platform compatibility

## Template Features

### C++ Template (base-cpp)
- **Modern C++**: Support for C++17/20/23
- **Build Systems**: CMake (primary), Meson (optional)
- **Testing**: GoogleTest integration
- **Code Quality**: clang-format, clang-tidy, pre-commit hooks
- **Performance**: sccache integration, Ninja build support
- **AI Integration**: Claude/Serena MCP ready

### Python Template (base-python)
- **Modern Python**: Support for Python 3.10/3.11/3.12
- **Fast Tooling**: Ruff for ultra-fast linting and formatting
- **Type Checking**: mypy integration
- **Testing**: pytest with coverage reporting
- **Packaging**: Modern pyproject.toml based packaging
- **Virtual Environment**: Automatic venv creation

## Development Workflow Integration

### Project Creation Workflow
1. **Template Selection**: Choose Python or C++ template
2. **Interactive Configuration**: Select project options
3. **Project Generation**: Cookiecutter creates project structure
4. **Environment Setup**: Automatic development environment configuration
5. **Initial Commit**: Git repository initialization with quality hooks

### AI-Enhanced Development
- **Context Detection**: Automatic AI context selection based on project type
- **Memory System**: Persistent project knowledge storage
- **Tool Integration**: Seamless development tool usage
- **Quality Assurance**: Automated code quality and validation

### Quality Assurance Workflow
1. **Pre-commit**: Code formatting, linting, syntax validation
2. **Pre-push**: Testing, build verification, security scanning
3. **Template Validation**: Prevention of domain code contamination
4. **Continuous Integration**: Automated quality gates

## Code Separation Principles

### Physical Separation
- **Domain Code**: Isolated in `moqui/` directory
- **Template Code**: Isolated in `templates/` directory
- **Shared Code**: Minimal, well-defined interfaces
- **No Cross-Contamination**: Strict validation prevents mixing

### Functional Separation
- **Moqui Domain**: Medical physics, Monte Carlo simulation
- **Template System**: Generic software development patterns
- **Clear Boundaries**: Well-defined interfaces between systems
- **Independent Operation**: Each system can operate independently

## Validation and Quality Assurance

### Template Validation
- **Contamination Prevention**: Automated checks for domain-specific terms
- **Structure Validation**: Template structure verification
- **Functionality Testing**: Generated project validation
- **Continuous Monitoring**: Ongoing template quality assurance

### System Integration Testing
- **Cross-System Validation**: Ensure systems don't interfere
- **Performance Testing**: No performance degradation in either system
- **Compatibility Testing**: Tools work correctly in both contexts
- **User Acceptance**: Both use cases work as expected

## Performance Benefits

### Development Speed
- **Project Creation**: 2-5 minutes vs 2-4 hours manual setup
- **Code Quality**: Instant automated quality checks
- **Tool Integration**: Pre-configured development environment
- **AI Assistance**: Context-aware AI development support

### Tool Performance
- **Python Linting**: Ruff is 100x faster than Black + Flake8
- **C++ Builds**: sccache provides 12x faster cached builds
- **Template Generation**: Cookiecutter creates projects instantly
- **Quality Validation**: Automated, instant feedback

## AI Integration Features

### Serena MCP Integration
- **Context Awareness**: Automatic project type detection
- **Memory System**: Persistent project knowledge
- **Tool Usage**: Native tool integration and automation
- **Error Correction**: Self-correcting development assistance

### AI Workflow Templates
- **Development Guidelines**: AI-ready project structure
- **Code Review Templates**: Standardized review processes
- **Testing Strategies**: Automated test generation
- **Documentation Standards**: AI-compatible documentation

## Usage Patterns

### Template Users
1. **New Project Creation**: Use templates for rapid project setup
2. **Best Practices**: Templates include modern development practices
3. **Tool Integration**: Pre-configured tools and workflows
4. **AI Assistance**: Enhanced development with AI workflows

### Domain Developers
1. **Moqui Development**: Continue using existing Moqui workflows
2. **AI Context**: Specialized AI context for physics development
3. **Quality Assurance**: Existing quality maintenance processes
4. **No Interference**: Template system doesn't affect domain development

## Maintenance and Evolution

### Template Maintenance
- **Regular Updates**: Keep templates updated with latest best practices
- **Tool Updates**: Maintain current tool versions
- **Feature Additions**: Add new features based on user feedback
- **Quality Assurance**: Ongoing template validation

### System Evolution
- **Additional Templates**: Support for more languages/frameworks
- **Enhanced AI Integration**: Improved AI workflow capabilities
- **Performance Optimization**: Continuous performance improvements
- **User Experience**: Enhanced user interfaces and workflows

## Troubleshooting and Support

### Common Issues
- **Template Validation**: Contamination detection and resolution
- **Project Type Detection**: Context selection issues
- **Tool Integration**: Development tool configuration
- **AI Context**: Memory system and context switching

### Support Resources
- **Documentation**: Comprehensive user and developer documentation
- **Examples**: Sample projects and use cases
- **Community**: User support and community contributions
- **AI Assistance**: Serena MCP with appropriate contexts

This template system overview provides the foundation for understanding how the CICD Template System works, its components, and its role in enabling rapid, high-quality project setup while maintaining clean separation from the domain-specific Moqui codebase.
