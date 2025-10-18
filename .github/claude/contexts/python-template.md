# Python Template AI Context

## Project Overview

This is the **Python Template** context for AI-assisted development of generic Python projects created from the CICD template system. This context should be used when working on Python template-based projects.

## Project Type

- **Type**: `python-template`
- **AI Context**: `python-project`
- **Primary Language**: Python
- **Build System**: Standard Python packaging (pyproject.toml)
- **Domain**: Generic Python Software Development

## Template Structure

### Standard Project Layout
```
{{cookiecutter.project_slug}}/
├── src/
│   └── {{cookiecutter.package_name}}/    # Source code
├── tests/                               # Test files
├── configs/                             # Configuration files
├── git-hooks/                           # Git hooks
├── .github/                             # GitHub integration
│   └── claude/
│       └── CLAUDE.md                    # AI context
├── pyproject.toml                       # Project configuration
├── README.md                            # Project documentation
├── LICENSE                              # License file
├── .ruff.toml                          # Ruff configuration
├── .pre-commit-config.yaml              # Pre-commit hooks
└── venv/                                # Virtual environment
```

### Key Template Features
- **Modern Python**: Support for Python 3.10/3.11/3.12
- **Fast Tooling**: Ruff for ultra-fast linting and formatting
- **Type Checking**: mypy integration for static type checking
- **Testing**: pytest framework with coverage
- **Packaging**: Modern pyproject.toml based packaging
- **AI Integration**: Claude/Serena MCP ready

## Development Guidelines

### Code Standards
- **Python Version**: Configurable (3.10/3.11/3.12)
- **Code Style**: Ruff (100x faster than Black + Flake8)
- **Type Hints**: Comprehensive type annotations
- **Error Handling**: Proper exception handling
- **Documentation**: Docstrings following Google/NumPy style

### Testing Strategy
- **Framework**: pytest with plugins
- **Coverage**: Coverage reporting with target coverage
- **Testing Types**: Unit, integration, and property-based tests
- **Continuous Testing**: Pre-commit hooks ensure tests pass

### Documentation Requirements
- **Docstrings**: All public functions and classes
- **README**: Comprehensive project documentation
- **API Docs**: Generated from docstrings
- **Examples**: Usage examples and tutorials

## Template Customization Options

### Cookiecutter Variables
- `project_name`: Display name for the project
- `project_slug`: URL-friendly project name
- `package_name`: Python package name
- `python_version`: Target Python version (3.10/3.11/3.12)
- `use_git_hooks`: Enable git hooks integration
- `include_docker`: Include Docker configuration
- `use_ai_workflow`: Enable AI workflow integration
- `license`: Project license type

### Python Tooling
- **Ruff**: Fast linting and formatting
- **pytest**: Testing framework with coverage
- **mypy**: Static type checking
- **pre-commit**: Git hooks management
- **Virtual Environment**: Automatic venv creation

## Common Tasks

### Creating New Projects
1. Use `scripts/create-project.sh python` command
2. Select desired options in interactive mode
3. Project is created with virtual environment
4. Dependencies are installed automatically
5. Initialize git repository and make initial commit

### Package Development
1. Activate virtual environment: `source venv/bin/activate`
2. Install dependencies: `pip install -e .`
3. Write code with proper type hints
4. Add comprehensive tests
5. Use Ruff for code formatting and linting

### Testing and Quality
1. Run tests: `pytest tests/`
2. Check coverage: `pytest --cov=src`
3. Type checking: `mypy src/`
4. Linting: `ruff check src/`
5. Formatting: `ruff format src/`

## Tools and Dependencies

### Development Tools
- **Ruff**: Ultra-fast Python linting and formatting
- **pytest**: Testing framework with rich ecosystem
- **mypy**: Static type checking
- **pre-commit**: Git hooks management
- **Virtual Environment**: Isolated Python environment

### Python Ecosystem
- **pip**: Package management
- **setuptools**: Build system backend
- **wheel**: Binary distribution format
- **twine**: Package uploading tool

### AI Integration
- **Claude Code**: AI development assistant
- **Serena MCP**: Enhanced AI capabilities
- **AI Contexts**: Project-specific AI guidance
- **Memory System**: Persistent project knowledge

## Quality Assurance

### Code Quality Checks
- **Formatting**: Automatic with Ruff
- **Linting**: Fast comprehensive linting with Ruff
- **Type Checking**: Static analysis with mypy
- **Testing**: Comprehensive test coverage

### Git Hooks
- **prepare-commit-msg**: Code formatting and validation
- **pre-commit**: Testing and type checking
- **pre-push**: Full quality checks and validation

### Performance Metrics
- **Ruff Speed**: 100x faster than traditional tools
- **Test Performance**: Fast test execution
- **Import Performance**: Optimized import structure
- **Runtime Performance**: Where applicable

## AI-Enhanced Development

### Serena MCP Integration
- **Context Awareness**: Python project type detection
- **Memory System**: Python-specific knowledge storage
- **Tool Integration**: Seamless Python development tools
- **Error Correction**: Self-correcting Python assistance

### AI-Assisted Features
- **Code Generation**: Generate Python boilerplate
- **Test Creation**: Automatic pytest test generation
- **Type Hints**: Suggest appropriate type annotations
- **Documentation**: Generate docstrings automatically
- **Refactoring**: Python code improvement suggestions

## Performance Considerations

### Development Performance
- **Fast Linting**: Ruff's exceptional speed
- **Quick Testing**: Efficient test execution
- **Smart Formatting**: Incremental formatting
- **Type Checking**: Fast mypy configuration

### Runtime Performance
- **Profiling**: Performance analysis tools
- **Optimization**: Python optimization techniques
- **Memory Usage**: Efficient memory management
- **Async Programming**: Where applicable

## Python Best Practices

### Code Organization
- **Package Structure**: Logical package organization
- **Import Style**: Consistent import ordering
- **Naming Conventions**: PEP 8 compliance
- **Module Design**: Cohesive, loosely coupled modules

### Dependency Management
- **pyproject.toml**: Modern dependency specification
- **Virtual Environments**: Isolated development environments
- **Version Pinning**: Appropriate version constraints
- **Security**: Regular dependency updates

### Error Handling
- **Exceptions**: Proper exception hierarchy
- **Logging**: Structured logging practices
- **Validation**: Input validation and sanitization
- **Graceful Failure**: Robust error handling

## Security Best Practices

### Code Security
- **Dependency Scanning**: Check for vulnerable packages
- **Secret Management**: No hardcoded secrets
- **Input Validation**: Proper input sanitization
- **Error Handling**: Secure error messages

### Development Security
- **Virtual Environments**: Isolated development
- **Package Verification**: Verify package integrity
- **Access Control**: Proper permissions
- **Code Review**: Security-focused reviews

## Deployment and Distribution

### Packaging
- **pyproject.toml**: Modern build configuration
- **Build Tools**: setuptools or other backends
- **Distribution**: PyPI publishing workflow
- **Versioning**: Semantic versioning

### Continuous Integration
- **Automated Testing**: CI pipeline integration
- **Quality Checks**: Automated quality validation
- **Security Scanning**: Automated security checks
- **Deployment**: Automated deployment processes

## Template Validation

### Contamination Prevention
- **Generic Code**: Templates remain domain-agnostic
- **Validation Scripts**: Automated contamination checks
- **Regular Audits**: Template quality validation
- **Clean Separation**: Clear boundaries from domain code

### Quality Assurance
- **Template Testing**: Validate generated projects
- **Cross-Platform**: Ensure template works across platforms
- **Tool Compatibility**: Validate Python tool integration
- **Documentation**: Complete and accurate documentation

## Advanced Features

### Optional Features
- **Docker Support**: Containerization when enabled
- **Documentation**: Sphinx documentation generation
- **Performance**: Profiling and optimization tools
- **Web Integration**: FastAPI/Flask integration options

### Integration Options
- **Database**: SQLAlchemy integration options
- **API Framework**: FastAPI/Flask template variants
- **CLI Tools**: Click/Typer integration
- **Data Science**: NumPy/Pandas integration

## Related Files and Contexts

- **Domain Context**: Use `.github/claude/contexts/moqui-domain.md` for Moqui work
- **Shared Context**: Use `.github/claude/contexts/shared-workflows.md` for common tasks
- **Template Knowledge**: Available in `.serena/memories/template-system-knowledge/`

## Contact and Support

- **Template System**: CICD Template development team
- **Python Community**: Python packaging and tooling community
- **AI Assistance**: Serena MCP with appropriate context
- **Documentation**: Template system and Python documentation
