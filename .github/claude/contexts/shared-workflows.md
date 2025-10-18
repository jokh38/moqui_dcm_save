# Shared Development Workflows

## Overview

This context contains **shared development workflows** that apply across all project types (Moqui domain, C++ templates, Python templates, and generic projects). These workflows represent best practices and common patterns for software development.

## Applicable Project Types

- **moqui-domain**: For Monte Carlo physics simulation
- **cpp-template**: For generic C++ projects
- **python-template**: For generic Python projects
- **generic**: For any other project types

## Common Development Workflows

### Git Workflow

#### Standard Git Process
```bash
# Start new work
git checkout -b feature/your-feature-name

# Make changes with automatic quality checks
git add .
git commit -m "feat: implement new feature"  # Hooks run automatically

# Push and create pull request
git push origin feature/your-feature-name
```

#### Commit Message Standards
- **Format**: Conventional Commits
- **Types**: feat, fix, docs, style, refactor, test, chore
- **Examples**:
  - `feat: add user authentication system`
  - `fix: resolve memory leak in data processing`
  - `docs: update API documentation`
  - `test: add unit tests for math utilities`

#### Branch Naming
- **Features**: `feature/description-of-feature`
- **Bug Fixes**: `fix/description-of-fix`
- **Documentation**: `docs/update-documentation`
- **Maintenance**: `chore/update-dependencies`

### Code Quality Workflow

#### Before Committing
1. **Code Formatting**: Automatic formatting (clang-format/ruff)
2. **Static Analysis**: Linting and type checking
3. **Syntax Validation**: Ensure code compiles/runs
4. **Basic Tests**: Run quick test suite

#### After Commit (Pre-push)
1. **Full Test Suite**: Comprehensive testing
2. **Build Verification**: Ensure project builds correctly
3. **Security Scanning**: Check for vulnerabilities
4. **Performance Tests**: Where applicable
5. **Dependency Checks**: Validate dependencies

### Testing Workflow

#### Test-Driven Development (TDD)
1. **Write Test**: Create failing test for new functionality
2. **Implement Code**: Write minimal code to pass test
3. **Refactor**: Improve code while maintaining test coverage
4. **Repeat**: Continue with next feature

#### Test Categories
- **Unit Tests**: Test individual functions/classes
- **Integration Tests**: Test component interactions
- **End-to-End Tests**: Test complete workflows
- **Performance Tests**: Validate performance requirements
- **Security Tests**: Check for security vulnerabilities

#### Test Best Practices
- **Descriptive Names**: Clear test names describing behavior
- **Arrange-Act-Assert**: Structure tests clearly
- **Test Coverage**: Aim for high coverage where meaningful
- **Mock Objects**: Use mocks for external dependencies
- **Data-Driven Tests**: Use parameterized tests where appropriate

### Documentation Workflow

#### Code Documentation
1. **API Documentation**: Document all public interfaces
2. **Inline Comments**: Explain complex logic
3. **Type Hints**: Use type annotations (Python) or clear types (C++)
4. **Examples**: Provide usage examples

#### Project Documentation
1. **README**: Comprehensive project overview
2. **Installation Guide**: Clear setup instructions
3. **Usage Guide**: How to use the software
4. **Contributing Guide**: Development setup and guidelines
5. **API Reference**: Detailed API documentation

#### Documentation Maintenance
- **Keep Updated**: Update docs with code changes
- **Examples**: Ensure examples work correctly
- **Screenshots**: Update screenshots for UI changes
- **Links**: Verify all links are valid

### Debugging Workflow

#### Systematic Debugging
1. **Reproduce Issue**: Create minimal reproduction case
2. **Isolate Problem**: Narrow down the scope
3. **Form Hypothesis**: Identify potential causes
4. **Test Hypothesis**: Verify or reject hypotheses
5. **Fix Issue**: Implement and test fix
6. **Verify Solution**: Ensure fix works and doesn't break other functionality

#### Debugging Tools
- **Logging**: Add structured logging
- **Debuggers**: Use appropriate debugging tools
- **Profiling**: Profile performance issues
- **Static Analysis**: Use static analysis tools
- **Code Review**: Get second opinions on complex issues

### Performance Optimization Workflow

#### Performance Analysis
1. **Baseline Measurement**: Establish current performance metrics
2. **Profile Application**: Identify bottlenecks
3. **Analyze Results**: Understand performance issues
4. **Optimize**: Implement targeted optimizations
5. **Validate**: Measure improvement and ensure correctness

#### Optimization Strategies
- **Algorithm Optimization**: Choose optimal algorithms
- **Data Structures**: Use appropriate data structures
- **Caching**: Implement caching where beneficial
- **Parallel Processing**: Use concurrency where appropriate
- **Memory Optimization**: Reduce memory usage

### Dependency Management Workflow

#### Regular Maintenance
1. **Audit Dependencies**: Check for security vulnerabilities
2. **Update Versions**: Update to stable, compatible versions
3. **Test Compatibility**: Ensure updates don't break functionality
4. **Document Changes**: Update documentation for dependency changes

#### Dependency Best Practices
- **Minimal Dependencies**: Use only necessary dependencies
- **Version Pinning**: Pin versions for reproducibility
- **Security Scanning**: Regular security audits
- **License Compatibility**: Ensure compatible licenses

## AI-Assisted Development Workflows

### Serena MCP Integration

#### Autonomous Development
```bash
# Enable Serena for autonomous development
claude "Analyze codebase and implement improvements"
# Serena will:
# - Analyze code quality
# - Implement improvements
# - Run tests and validation
# - Create commits with proper messages
```

#### Code Generation
```bash
# Generate boilerplate code
claude "Generate unit tests for the math utilities module"
# Serena will:
# - Analyze existing code
# - Generate comprehensive tests
# - Ensure test coverage
# - Validate test functionality
```

#### Documentation Generation
```bash
# Generate documentation
claude "Update API documentation for current codebase"
# Serena will:
# - Analyze code structure
# - Generate API docs
# - Create examples
# - Update README files
```

### AI Workflow Patterns

#### Development Assistant Mode
- **Planning Mode**: Use for architectural decisions
- **Editing Mode**: Use for focused code changes
- **Interactive Mode**: Use for collaborative development
- **Autonomous Mode**: Use for self-directed development

#### Context Management
- **Project Type Detection**: Automatic context selection
- **Memory System**: Persistent project knowledge
- **Context Switching**: Seamless transitions between project types
- **Tool Integration**: Native tool usage and automation

## Tool Integration Workflows

### Development Environment Setup

#### Initial Setup
1. **Clone Repository**: Get the source code
2. **Install Dependencies**: Set up development environment
3. **Configure Tools**: Set up linting, formatting, etc.
4. **Initialize Git Hooks**: Set up automated quality checks
5. **Verify Setup**: Run validation scripts

#### Environment Validation
```bash
# Validate development environment
scripts/validate-setup.sh

# Check specific tools
which clang-format ruff pytest mypy cmake

# Run full validation
make validate  # or equivalent
```

### Build and Deploy Workflow

#### Local Development
1. **Make Changes**: Edit source code
2. **Build Project**: Compile/build the project
3. **Run Tests**: Execute test suite
4. **Quality Checks**: Run linting and analysis
5. **Debug**: Fix any issues found

#### Continuous Integration
1. **Automated Build**: CI server builds project
2. **Automated Testing**: Run full test suite
3. **Quality Gates**: Enforce quality standards
4. **Security Scanning**: Check for vulnerabilities
5. **Deploy**: Deploy if all checks pass

## Quality Assurance Workflows

### Code Review Process

#### Review Checklist
- **Functionality**: Code works as intended
- **Testing**: Adequate test coverage
- **Performance**: Acceptable performance
- **Security**: No security vulnerabilities
- **Documentation**: Appropriate documentation
- **Style**: Follows project style guidelines

#### Review Best Practices
- **Constructive Feedback**: Provide helpful, specific feedback
- **Thorough Review**: Review all changes carefully
- **Discussion**: Discuss significant changes
- **Approval**: Clear approval process

### Release Workflow

#### Pre-Release Checklist
- **Testing**: All tests pass
- **Documentation**: Documentation is updated
- **Version**: Version number is updated
- **Changelog**: Changelog is updated
- **Security**: Security scan passes

#### Release Process
1. **Tag Release**: Create git tag
2. **Build Artifacts**: Create distribution packages
3. **Test Release**: Test release artifacts
4. **Publish**: Publish to repository
5. **Announce**: Announce release

## Troubleshooting Workflows

### Common Issues

#### Build Issues
1. **Check Dependencies**: Verify all dependencies are installed
2. **Clean Build**: Clean and rebuild from scratch
3. **Compiler Errors**: Fix compiler errors systematically
4. **Linker Errors**: Resolve linking issues
5. **Configuration**: Check build configuration

#### Test Failures
1. **Isolate Test**: Run specific failing test
2. **Debug Output**: Add debug logging
3. **Check Environment**: Verify test environment
4. **Update Tests**: Update tests if requirements changed
5. **Fix Code**: Fix underlying code issues

#### Performance Issues
1. **Profile**: Profile to identify bottlenecks
2. **Analyze**: Analyze profiling results
3. **Optimize**: Implement targeted optimizations
4. **Measure**: Verify performance improvements
5. **Validate**: Ensure optimizations don't break functionality

## Project-Specific Adaptations

### Moqui Domain Adaptations
- **Physics Validation**: Validate computational physics accuracy
- **Performance**: Prioritize Monte Carlo simulation speed
- **Numerical Stability**: Ensure numerical precision
- **Regulatory Compliance**: Follow medical device standards

### Template System Adaptations
- **Generic Code**: Ensure templates remain domain-agnostic
- **Validation**: Prevent code contamination
- **Flexibility**: Support multiple configuration options
- **Documentation**: Comprehensive template documentation

### Language-Specific Adaptations

#### C++ Specific
- **Memory Management**: Proper RAII and smart pointer usage
- **Template Usage**: Appropriate use of C++ templates
- **Build System**: CMake/Meson configuration
- **Static Analysis**: clang-tidy integration

#### Python Specific
- **Type Hints**: Comprehensive type annotations
- **Virtual Environments**: Isolated Python environments
- **Package Management**: Modern pyproject.toml usage
- **Testing**: pytest and coverage integration

## Continuous Improvement

### Process Enhancement
- **Regular Review**: Review and improve development processes
- **Tool Updates**: Keep tools updated and configured optimally
- **Feedback Loop**: Collect and act on team feedback
- **Training**: Continuous learning and skill development

### Metrics and Monitoring
- **Quality Metrics**: Track code quality metrics over time
- **Performance Metrics**: Monitor development and application performance
- **Productivity Metrics**: Measure development efficiency
- **Satisfaction**: Track team satisfaction with tools and processes

This shared workflows context provides a foundation for consistent, high-quality development across all project types while allowing for project-specific adaptations and optimizations.
