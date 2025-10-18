# 📋 Development Plan 01: CICD Template System Implementation

## 🎯 Executive Summary

This document outlines the comprehensive implementation plan to transform the **moqui_dcm_save** project from a specialized Moqui Monte Carlo dose calculation system into a general-purpose **CICD Template system** for creating new projects with AI-enhanced development workflows.

**Creation Date**: 2025-10-18
**Status**: Planning Phase
**Version**: 1.0

## 📊 Current Status Assessment

### ✅ **Strengths (Already Implemented)**
- **Advanced Moqui Monte Carlo Engine** (100%): Sophisticated 2D dose calculation, DICOM integration
- **AI-Enhanced Features** (85%): Serena MCP integration, comprehensive documentation
- **Modern C++ Build System** (95%): CMake, GoogleTest, code quality tools
- **Code Quality Framework** (80%): clang-format/clang-tidy, pre-push hooks

### ❌ **Critical Missing Components**
- **Cookiecutter Templates**: Project generation system
- **Git Hooks Infrastructure**: prepare-commit-msg, git-hooks/ directory
- **Setup Scripts**: Development environment automation
- **Project Creation Tools**: scripts/create-project.sh

### 📈 **Implementation Completeness**: 70-75%

## 🏗️ Implementation Roadmap

### **Phase 1: Foundation Infrastructure** (Weeks 1-2)
**Priority**: 🔴 Critical - Core template functionality

#### 1.1 Project Structure Reorganization
```
moqui_dcm_save/
├── cookiecutters/
│   ├── python-project/
│   │   ├── {{cookiecutter.project_slug}}/
│   │   │   ├── src/
│   │   │   ├── tests/
│   │   │   ├── configs/
│   │   │   ├── git-hooks/
│   │   │   └── .github/
│   │   │       └── claude/
│   │   │           └── CLAUDE.md
│   │   ├── cookiecutter.json
│   │   └── hooks/
│   │       └── post_gen_project.py
│   └── cpp-project/
│       ├── {{cookiecutter.project_slug}}/
│       │   ├── src/
│       │   ├── include/
│       │   ├── tests/
│       │   ├── configs/
│       │   ├── git-hooks/
│       │   └── .github/
│       │       └── claude/
│       │           └── CLAUDE.md
│       ├── cookiecutter.json
│       └── hooks/
│           └── post_gen_project.py
└── scripts/
    └── create-project.sh
```

#### 1.2 Core Files to Create

**`scripts/create-project.sh`**
```bash
#!/bin/bash
# Main project creation script with interactive and non-interactive modes
# Supports Python and C++ project types with AI workflow integration

Usage: create-project.sh <python|cpp> [path] [--github] [--ai-workflow]

Features:
- Interactive project configuration
- Cookiecutter template execution
- Git repository initialization
- AI workflow template integration
- GitHub repository creation (optional)
```

**`cookiecutters/python-project/cookiecutter.json`**
```json
{
    "project_name": "My Python Project",
    "project_slug": "{{ cookiecutter.project_name.lower().replace(' ', '_') }}",
    "package_name": "{{ cookiecutter.project_slug }}",
    "python_version": ["3.10", "3.11", "3.12"],
    "use_git_hooks": "yes",
    "include_docker": "no",
    "use_ai_workflow": "yes",
    "license": ["MIT", "BSD-3-Clause", "Apache-2.0", "GPL-3.0", "None"]
}
```

**`cookiecutters/cpp-project/cookiecutter.json`**
```json
{
    "project_name": "My C++ Project",
    "cpp_standard": ["17", "20", "23"],
    "build_system": ["cmake", "meson"],
    "use_ai_workflow": "yes",
    "enable_cache": "yes",
    "use_ninja": "yes",
    "testing_framework": ["gtest", "catch2", "doctest"],
    "license": ["MIT", "BSD-3-Clause", "Apache-2.0", "GPL-3.0", "None"]
}
```

### **Phase 2: Git Hooks Implementation** (Week 3)
**Priority**: 🔴 Critical - Local CI/CD functionality

#### 2.1 Git Hooks Structure
```
git-hooks/
├── prepare-commit-msg      # Commit message validation
└── pre-commit              # Code quality checks
```

#### 2.2 Hook Implementation Details

**`git-hooks/prepare-commit-msg`**
```bash
#!/bin/bash
# Commit message validation hook for conventional commit format
# Integrates with code formatting and linting tools

Features:
- Conventional commit format validation
- Automatic code formatting (ruff/clang-format)
- Static analysis execution (mypy/clang-tidy)
- Syntax validation
```

**Enhanced `git-hooks/pre-commit`**
```bash
#!/bin/bash
# Enhanced pre-commit hook with comprehensive testing and validation

Features:
- Testing (pytest/ctest)
- Build verification
- Security scanning
- Dependency checks
- Performance analysis
```

### **Phase 3: Setup Scripts Development** (Week 4)
**Priority**: 🟡 Medium - Developer experience

#### 3.1 Setup Scripts Structure
```
setup-scripts/
├── total_run.sh            # Linux setup
├── total_run.ps1           # Windows PowerShell setup
├── linux/
│   ├── install-tools.sh
│   ├── validate-setup.sh
│   └── validation/
│       ├── check-python-tools.sh
│       ├── check-cpp-tools.sh
│       └── check-git-hooks.sh
└── windows/
    ├── install-tools.ps1
    ├── validate-setup.ps1
    └── validation/
        ├── check-python-tools.ps1
        ├── check-cpp-tools.ps1
        └── check-git-hooks.ps1
```

#### 3.2 Tool Installation Automation

**Linux Tools to Install**:
- Python: ruff, pytest, mypy, cookiecutter
- C++: cmake, ninja-build, clang-format, clang-tidy, sccache
- General: git, gh (GitHub CLI), pre-commit

**Windows Tools to Install**:
- Python: ruff, pytest, mypy, cookiecutter (via pip)
- C++: cmake, ninja, clang-format, clang-tidy, sccache (via Chocolatey)
- General: git, gh, pre-commit

### **Phase 4: Template Content Creation** (Weeks 5-6)
**Priority**: 🟡 Medium - Template completeness

#### 4.1 Python Template Features
- **Ruff configuration**: Fast linting and formatting (100x faster than Black + Flake8)
- **pytest setup**: Testing framework with coverage reporting
- **mypy integration**: Static type checking
- **Virtual environment**: Automatic venv creation and dependency management
- **AI workflow templates**: Claude integration files
- **Pre-commit hooks**: Comprehensive code quality validation

#### 4.2 C++ Template Features
- **CMake/Meson support**: Flexible build system support
- **GoogleTest integration**: Unit testing framework
- **clang-format/clang-tidy**: Code formatting and static analysis
- **sccache integration**: Compilation caching for faster builds
- **AI workflow templates**: Enhanced development features
- **Pre-commit hooks**: Build verification and testing validation

#### 4.3 AI Enhancement Features (Both Templates)
- **Claude Integration**: Pre-configured AI assistant context
- **Serena MCP**: Model Context Protocol server for enhanced AI capabilities
- **Automated Labels**: GitHub labels for AI workflow triggering
- **Documentation Templates**: AI-ready project documentation
- **Quality Gates**: Automated code quality and validation checks

### **Phase 5: Documentation and Integration** (Weeks 7-8)
**Priority**: 🟢 Low - Documentation and polish

#### 5.1 Documentation Creation
```
docs/
├── manuals/
│   ├── QUICK_START.md
│   ├── COOKIECUTTER_GUIDE.md
│   ├── TROUBLESHOOTING.md
│   └── AI_WORKFLOWS.md
├── examples/
│   ├── python-example/
│   │   ├── README.md
│   │   ├── src/
│   │   └── tests/
│   └── cpp-example/
│       ├── README.md
│       ├── src/
│       ├── include/
│       └── tests/
└── api/
    └── TEMPLATE_REFERENCE.md
```

#### 5.2 Integration Testing
- **End-to-end project creation**: Test template generation
- **Tool validation**: Verify all tools work correctly
- **Performance benchmarking**: Measure improvement metrics
- **Cross-platform testing**: Linux and Windows compatibility

## 🔧 Integration Strategy

### **Backward Compatibility**
- **Preserve existing Moqui functionality**: No changes to core Monte Carlo engine
- **Maintain current build system**: CMake configuration remains functional
- **Keep AI features intact**: Serena MCP integration continues to work

### **Gradual Implementation**
- **Phase-based approach**: Each phase can be completed independently
- **Incremental testing**: Validate each component before proceeding
- **Feature flags**: Enable/disable new features during development

### **File Organization**
- **Clear separation**: Template files separate from existing Moqui code
- **Modular structure**: Each component is self-contained
- **Extensible design**: Easy to add new templates and features

## 🧪 Testing and Validation Plan

### **Unit Testing**
- **Script functionality**: Test each script with various inputs
- **Template generation**: Verify cookiecutter templates work correctly
- **Hook execution**: Test git hooks with different scenarios

### **Integration Testing**
- **End-to-end project creation**: Test complete workflow from script to usable project
- **Tool compatibility**: Verify all tools work together correctly
- **Cross-platform testing**: Test on Linux and Windows environments

### **Performance Validation**
- **Project creation speed**: Measure template generation time
- **Build performance**: Verify sccache integration improves build times
- **Tool execution speed**: Validate performance improvements vs traditional setup

### **Quality Assurance**
- **Code coverage**: Ensure comprehensive test coverage
- **Security scanning**: Validate setup scripts and templates
- **Documentation accuracy**: Verify all documentation matches functionality

## 📊 Priority Matrix

| Component | Impact | Effort | Priority | Dependencies |
|-----------|--------|--------|----------|--------------|
| Cookiecutter Templates | 🔴 High | 🟡 Medium | 🔴 Critical | None |
| Project Creation Script | 🔴 High | 🟡 Medium | 🔴 Critical | Templates |
| Git Hooks | 🔴 High | 🟢 Low | 🔴 Critical | None |
| Setup Scripts | 🟡 Medium | 🔴 High | 🟡 Medium | Git Hooks |
| Documentation | 🟢 Low | 🟡 Medium | 🟢 Low | All Components |

## 🎯 Success Metrics

### **Functional Requirements**
- ✅ **Project Creation**: < 5 minutes to create new project
- ✅ **Tool Integration**: All tools configured and working
- ✅ **AI Workflows**: Serena MCP integration functional
- ✅ **Cross-platform**: Linux and Windows support

### **Performance Requirements**
- ✅ **100x faster** project setup vs manual (2-4 hours → 2-5 minutes)
- ✅ **12x faster** Python linting (Black+Flake8 → Ruff)
- ✅ **2x faster** C++ builds (with sccache)
- ✅ **Instant** code quality validation

### **Quality Requirements**
- ✅ **Automated testing**: All projects include comprehensive test setup
- ✅ **Code quality**: Consistent formatting and linting across all projects
- ✅ **Documentation**: Complete and up-to-date documentation
- ✅ **AI integration**: Seamless Claude/Serena integration

## 🚀 Implementation Timeline

| Week | Phase | Deliverables |
|------|-------|--------------|
| 1-2 | Phase 1: Foundation | Cookiecutter templates, project creation script |
| 3 | Phase 2: Git Hooks | Complete git hooks implementation |
| 4 | Phase 3: Setup Scripts | Development environment automation |
| 5-6 | Phase 4: Templates | Complete Python and C++ templates |
| 7-8 | Phase 5: Documentation | Complete documentation and integration testing |

## 📋 Detailed Implementation Checklists

### **Phase 1 Checklist**
- [ ] Create `cookiecutters/` directory structure
- [ ] Implement Python cookiecutter template
- [ ] Implement C++ cookiecutter template
- [ ] Create `scripts/create-project.sh`
- [ ] Add post-generation hooks
- [ ] Test basic template generation

### **Phase 2 Checklist**
- [ ] Create `git-hooks/` directory
- [ ] Implement `prepare-commit-msg` hook
- [ ] Enhance `pre-commit` hook
- [ ] Add hook installation scripts
- [ ] Test hook functionality

### **Phase 3 Checklist**
- [ ] Create `setup-scripts/` directory
- [ ] Implement Linux setup script
- [ ] Implement Windows setup script
- [ ] Add validation scripts
- [ ] Test on both platforms

### **Phase 4 Checklist**
- [ ] Complete Python template content
- [ ] Complete C++ template content
- [ ] Add AI workflow integration
- [ ] Include comprehensive examples
- [ ] Test all template features

### **Phase 5 Checklist**
- [ ] Create comprehensive documentation
- [ ] Add examples and tutorials
- [ ] Implement integration testing
- [ ] Performance benchmarking
- [ ] Final validation and polish

## 🔗 Related Documents

- **CLAUDE.md**: Complete CICD Template system specification
- **docs/01_2d_dose_documentation.md**: Moqui 2D dose calculation implementation
- **docs/01_plan_2d_dose.md**: 2D dose calculation development plan
- **README.md**: Project overview and setup instructions

## 📝 Notes

### **Assumptions**
1. User has basic familiarity with Git and command line tools
2. Development environment supports Docker (optional)
3. Internet connection is available for tool installation
4. User has appropriate permissions for system-level tool installation

### **Risks and Mitigations**
1. **Tool Compatibility**: Regular testing across different OS versions
2. **Dependency Conflicts**: Use virtual environments and containerization
3. **User Experience**: Comprehensive documentation and examples
4. **Maintenance**: Automated testing and CI/CD for the template system itself

### **Future Enhancements**
1. **Additional Templates**: JavaScript, Rust, Go templates
2. **Cloud Integration**: AWS, Azure, GCP deployment templates
3. **Advanced AI Features**: More sophisticated Serena MCP workflows
4. **Template Marketplace**: Community-contributed templates

---

## 📞 Contact and Support

For questions about this implementation plan or to contribute to the development:

- **Project Repository**: https://github.com/jokh38/moqui_dcm_save
- **Documentation**: See related documents listed above
- **AI Assistant**: Use Serena MCP with Claude Code for development assistance

---

*This implementation plan provides a comprehensive roadmap for transforming the moqui_dcm_save project into a full-featured CICD Template system with AI-enhanced development workflows.*
