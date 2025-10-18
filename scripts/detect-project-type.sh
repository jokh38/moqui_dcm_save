#!/bin/bash

# Project Type Detection Script for CICD Template System
# This script detects the project type and sets appropriate AI context
# Usage: source scripts/detect-project-type.sh

set -euo pipefail

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Logging function
log() {
    echo -e "${BLUE}[DETECT]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1" >&2
}

success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Project type detection function
detect-project-type() {
    local script_dir
    script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    local project_root
    project_root="$(cd "$script_dir/.." && pwd)"

    log "Detecting project type in: $project_root"

    # Check if we're in the main repository (both systems available) - FIRST PRIORITY
    if [ -d "$project_root/moqui" ] && [ -d "$project_root/templates" ]; then
        export PROJECT_TYPE="dual-system"
        export AI_CONTEXT="development-environment"
        export PROJECT_PATH="$project_root"
        export BUILD_SYSTEM="mixed"
        export LANGUAGE="mixed"
        success "Detected Dual System Repository (Moqui + Templates)"
        log "Project Type: $PROJECT_TYPE"
        log "AI Context: $AI_CONTEXT"
        log "Project Path: $PROJECT_PATH"
        return 0
    fi

    # Check for Moqui domain project
    if [ -f "$project_root/moqui/CMakeLists.txt" ] || [ -f "$project_root/.moqui-project" ]; then
        export PROJECT_TYPE="moqui-domain"
        export AI_CONTEXT="monte-carlo-physics"
        export PROJECT_PATH="$project_root/moqui"
        export BUILD_SYSTEM="cmake"
        export LANGUAGE="cpp"
        success "Detected Moqui Domain Project"
        log "Project Type: $PROJECT_TYPE"
        log "AI Context: $AI_CONTEXT"
        log "Project Path: $PROJECT_PATH"
        return 0
    fi

    # Check for Python template project
    if [ -f "$project_root/pyproject.toml" ]; then
        # Check if it's a cookiecutter-generated Python project
        if grep -q "python-project" "$project_root/.cookiecutter.json" 2>/dev/null || \
           [ -f "$project_root/.python-template" ]; then
            export PROJECT_TYPE="python-template"
            export AI_CONTEXT="python-project"
            export PROJECT_PATH="$project_root"
            export BUILD_SYSTEM="python"
            export LANGUAGE="python"
            success "Detected Python Template Project"
            log "Project Type: $PROJECT_TYPE"
            log "AI Context: $AI_CONTEXT"
            log "Project Path: $PROJECT_PATH"
            return 0
        fi
    fi

    # Check for C++ template project
    if [ -f "$project_root/CMakeLists.txt" ] && [ ! -f "$project_root/moqui/CMakeLists.txt" ]; then
        # Check if it's a cookiecutter-generated C++ project
        if grep -q "cpp-project" "$project_root/.cookiecutter.json" 2>/dev/null || \
           [ -f "$project_root/.cpp-template" ]; then
            export PROJECT_TYPE="cpp-template"
            export AI_CONTEXT="cpp-project"
            export PROJECT_PATH="$project_root"
            export BUILD_SYSTEM="cmake"
            export LANGUAGE="cpp"
            success "Detected C++ Template Project"
            log "Project Type: $PROJECT_TYPE"
            log "AI Context: $AI_CONTEXT"
            log "Project Path: $PROJECT_PATH"
            return 0
        fi
    fi

    # Default fallback
    export PROJECT_TYPE="generic"
    export AI_CONTEXT="generic-project"
    export PROJECT_PATH="$project_root"
    export BUILD_SYSTEM="unknown"
    export LANGUAGE="unknown"
    warning "Could not determine specific project type, using generic settings"
    log "Project Type: $PROJECT_TYPE"
    log "AI Context: $AI_CONTEXT"
    log "Project Path: $PROJECT_PATH"
    return 0
}

# Project information display function
show-project-info() {
    detect-project-type

    echo
    log "=== Project Information ==="
    log "Type: $PROJECT_TYPE"
    log "AI Context: $AI_CONTEXT"
    log "Build System: $BUILD_SYSTEM"
    log "Language: $LANGUAGE"
    log "Path: $PROJECT_PATH"
    echo

    # Show type-specific information
    case "$PROJECT_TYPE" in
        "moqui-domain")
            log "Moqui Monte Carlo Physics Simulation"
            log "Features: DICOM integration, dose calculation, physics engine"
            ;;
        "python-template")
            log "Python Project Template"
            log "Features: Ruff, pytest, mypy, modern Python packaging"
            ;;
        "cpp-template")
            log "C++ Project Template"
            log "Features: CMake, GoogleTest, clang-format, sccache"
            ;;
        "dual-system")
            log "Dual System: Moqui Domain + CICD Templates"
            log "Features: Complete development environment with both systems"
            ;;
        *)
            log "Generic Project"
            log "Features: Standard development tools"
            ;;
    esac
}

# Validation function
validate-project-detection() {
    detect-project-type

    log "Validating project detection..."

    case "$PROJECT_TYPE" in
        "moqui-domain")
            if [ ! -f "$PROJECT_PATH/CMakeLists.txt" ]; then
                error "Moqui CMakeLists.txt not found at $PROJECT_PATH/CMakeLists.txt"
                return 1
            fi
            if [ ! -d "$PROJECT_PATH/src" ]; then
                error "Moqui source directory not found at $PROJECT_PATH/src"
                return 1
            fi
            ;;
        "python-template")
            if [ ! -f "$PROJECT_PATH/pyproject.toml" ]; then
                error "Python pyproject.toml not found at $PROJECT_PATH/pyproject.toml"
                return 1
            fi
            ;;
        "cpp-template")
            if [ ! -f "$PROJECT_PATH/CMakeLists.txt" ]; then
                error "C++ CMakeLists.txt not found at $PROJECT_PATH/CMakeLists.txt"
                return 1
            fi
            ;;
        "dual-system")
            if [ ! -d "$PROJECT_PATH/moqui" ]; then
                error "Moqui directory not found in dual system"
                return 1
            fi
            if [ ! -d "$PROJECT_PATH/templates" ]; then
                error "Templates directory not found in dual system"
                return 1
            fi
            ;;
    esac

    success "Project validation passed"
    return 0
}

# Export function for use in other scripts
export-detection-results() {
    detect-project-type

    log "Exporting project detection results..."

    # Create environment file for other scripts
    local env_file="/tmp/project-detection-env.sh"
    cat > "$env_file" << EOF
export PROJECT_TYPE="$PROJECT_TYPE"
export AI_CONTEXT="$AI_CONTEXT"
export PROJECT_PATH="$PROJECT_PATH"
export BUILD_SYSTEM="$BUILD_SYSTEM"
export LANGUAGE="$LANGUAGE"
EOF

    log "Environment variables exported to: $env_file"
    success "Detection results exported"
}

# Main execution
case "${1:-detect}" in
    "detect"|"--detect"|"-d")
        detect-project-type
        ;;
    "info"|"--info"|"-i")
        show-project-info
        ;;
    "validate"|"--validate"|"-v")
        validate-project-detection
        ;;
    "export"|"--export"|"-e")
        export-detection-results
        ;;
    "help"|"--help"|"-h")
        echo "Project Type Detection Script"
        echo
        echo "Usage: $0 [COMMAND]"
        echo
        echo "Commands:"
        echo "  detect, -d     Detect project type (default)"
        echo "  info, -i       Show detailed project information"
        echo "  validate, -v   Validate project detection"
        echo "  export, -e     Export detection results to environment file"
        echo "  help, -h       Show this help message"
        echo
        echo "Environment Variables Set:"
        echo "  PROJECT_TYPE   Type of project (moqui-domain, python-template, cpp-template, etc.)"
        echo "  AI_CONTEXT     AI context for workflows (monte-carlo-physics, python-project, etc.)"
        echo "  PROJECT_PATH   Path to the project root or specific project directory"
        echo "  BUILD_SYSTEM   Build system used (cmake, python, etc.)"
        echo "  LANGUAGE       Programming language (cpp, python, etc.)"
        ;;
    *)
        error "Unknown command: $1"
        echo "Use '$0 --help' for usage information"
        exit 1
        ;;
esac
