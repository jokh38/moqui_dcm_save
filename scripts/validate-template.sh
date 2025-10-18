#!/bin/bash

# Template Validation Script for CICD Template System
# This script validates that templates remain generic and free from domain contamination
# Usage: scripts/validate-template.sh [template_path]

set -euo pipefail

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Logging functions
log() {
    echo -e "${BLUE}[VALIDATE]${NC} $1"
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

# Configuration
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
TEMPLATES_DIR="${1:-$PROJECT_ROOT/templates}"

# Domain-specific terms that should NOT appear in templates
DOMAIN_TERMS=(
    "moqui"
    "dicom"
    "monte.*carlo"
    "dose.*calculation"
    "radiotherapy"
    "particle.*therapy"
    "proton.*therapy"
    "ion.*therapy"
    "linear.*accelerator"
    "treatment.*planning"
    "ct.*scan"
    "magnetic.*resonance"
    "radiation.*oncology"
    "beam.*modelling"
    "photon.*beam"
    "electron.*beam"
    "range.*shifter"
    "compensator"
    "aperture"
    "multi.*leaf.*collimator"
    "gantry"
    "patient.*positioning"
    "treatment.*machine"
    "scorer"
    "phantom"
    "waterphantom"
    "tissue.*density"
    "stopping.*power"
    "bragg.*peak"
    "spread.*out.*bragg.*peak"
    "treatment.*session"
    "beam.*source"
    "fluence"
    "energy.*deposit"
    "linear.*energy.*transfer"
    "biological.*effective.*dose"
    "gy"
    "gray"
    "sv"
    "sievert"
    "mqi_"
    "moqui_dcm_save"
)

# Template validation function
validate-template() {
    local template_path="$1"
    local validation_errors=0
    local validation_warnings=0

    log "Validating template: $template_path"

    # Check if template directory exists
    if [ ! -d "$template_path" ]; then
        error "Template directory does not exist: $template_path"
        return 1
    fi

    # Search for domain-specific terms
    log "Checking for domain-specific code contamination..."

    for term in "${DOMAIN_TERMS[@]}"; do
        # Use grep with case-insensitive search and word boundaries where appropriate
        if grep -r -i -E "$term" "$template_path" --exclude-dir=.git --exclude="*.md" 2>/dev/null; then
            error "Domain-specific term found: $term"
            ((validation_errors++))
        fi
    done

    # Check for specific Moqui file patterns
    log "Checking for Moqui-specific file patterns..."

    local moqui_files=(
        "mqi_*.hpp"
        "mqi_*.cpp"
        "*treatment*"
        "*dose*"
        "*dicom*"
        "*monte*"
        "*carlo*"
        "*beam*"
        "*scorer*"
        "*phantom*"
    )

    for pattern in "${moqui_files[@]}"; do
        if find "$template_path" -name "$pattern" -type f 2>/dev/null | grep -q .; then
            error "Moqui-specific file pattern found: $pattern"
            ((validation_errors++))
        fi
    done

    # Check for domain-specific include patterns
    log "Checking for domain-specific include patterns..."

    local domain_includes=(
        "moqui/"
        "mqi_"
        "dicom"
        "treatment"
        "monte"
        "carlo"
    )

    for include in "${domain_includes[@]}"; do
        if grep -r -i "#include.*$include" "$template_path" --include="*.cpp" --include="*.hpp" 2>/dev/null; then
            error "Domain-specific include found: $include"
            ((validation_errors++))
        fi
    done

    # Check for CMakeLists.txt with domain references
    log "Checking CMakeLists.txt for domain references..."

    if [ -f "$template_path/CMakeLists.txt" ]; then
        for term in "${DOMAIN_TERMS[@]}"; do
            if grep -i -E "$term" "$template_path/CMakeLists.txt" 2>/dev/null; then
                error "Domain-specific term in CMakeLists.txt: $term"
                ((validation_errors++))
            fi
        done
    fi

    # Validate template structure
    log "Validating template structure..."

    local expected_dirs=(
        "{{cookiecutter.project_slug}}"
        "hooks"
    )

    for dir in "${expected_dirs[@]}"; do
        if [ ! -d "$template_path/$dir" ]; then
            warning "Missing expected directory: $dir"
            ((validation_warnings++))
        fi
    done

    # Check for cookiecutter.json
    if [ ! -f "$template_path/cookiecutter.json" ]; then
        error "Missing cookiecutter.json file"
        ((validation_errors++))
    else
        log "Validating cookiecutter.json..."
        # Basic JSON validation
        if python3 -m json.tool "$template_path/cookiecutter.json" >/dev/null 2>&1; then
            success "cookiecutter.json is valid JSON"
        else
            error "cookiecutter.json is not valid JSON"
            ((validation_errors++))
        fi
    fi

    # Report results
    echo
    log "=== Validation Results ==="

    if [ $validation_errors -eq 0 ]; then
        success "Template validation PASSED"
        success "No domain contamination detected"
        success "Template structure is valid"
    else
        error "Template validation FAILED"
        error "Found $validation_errors error(s)"
        if [ $validation_warnings -gt 0 ]; then
            warning "Found $validation_warnings warning(s)"
        fi
    fi

    echo
    log "Summary:"
    log "  Errors: $validation_errors"
    log "  Warnings: $validation_warnings"

    return $validation_errors
}

# Batch validation function
validate-all-templates() {
    local templates_dir="$1"
    local total_errors=0

    log "Validating all templates in: $templates_dir"

    if [ ! -d "$templates_dir" ]; then
        error "Templates directory does not exist: $templates_dir"
        return 1
    fi

    # Find all template directories (containing cookiecutter.json)
    while IFS= read -r -d '' template; do
        log "========================================"
        validate-template "$(dirname "$template")"
        total_errors=$((total_errors + $?))
        log "========================================"
        echo
    done < <(find "$templates_dir" -name "cookiecutter.json" -print0)

    if [ $total_errors -eq 0 ]; then
        success "All templates passed validation"
    else
        error "Validation failed for one or more templates"
    fi

    return $total_errors
}

# Continuous monitoring function
monitor-templates() {
    local templates_dir="$1"
    local interval="${2:-300}" # Default 5 minutes

    log "Starting continuous template monitoring..."
    log "Monitoring directory: $templates_dir"
    log "Check interval: ${interval} seconds"
    log "Press Ctrl+C to stop monitoring"

    while true; do
        echo
        log "Running template validation check..."
        if validate-all-templates "$templates_dir"; then
            success "All templates are clean"
        else
            error "Template contamination detected!"
        fi
        echo
        log "Next check in ${interval} seconds..."
        sleep "$interval"
    done
}

# Create template validation configuration
create-validation-config() {
    local config_file="$PROJECT_ROOT/.template-validation-config"

    log "Creating template validation configuration..."

    cat > "$config_file" << 'EOF'
# Template Validation Configuration
# This file configures the template validation system

# Domain terms to check for (comma-separated)
DOMAIN_TERMS=moqui,dicom,monte.*carlo,dose.*calculation,radiotherapy,particle.*therapy,proton.*therapy,ion.*therapy,linear.*accelerator,treatment.*planning,ct.*scan,magnetic.*resonance,radiation.*oncology,beam.*modelling,photon.*beam,electron.*beam,range.*shifter,compensator,aperture,multi.*leaf.*collimator,gantry,patient.*positioning,treatment.*machine,scorer,phantom,waterphantom,tissue.*density,stopping.*power,bragg.*peak,spread.*out.*bragg.*peak,treatment.*session,beam.*source,fluence,energy.*deposit,linear.*energy.*transfer,biological.*effective.*dose,gy,gray,sv,sievert,mqi_,moqui_dcm_save

# File patterns to exclude from validation
EXCLUDE_PATTERNS=*.md,*.txt,.git/*,*.backup,*~

# Directories to exclude from validation
EXCLUDE_DIRS=.git,.gitignore,__pycache__,node_modules,.vscode,.idea

# Validation level: strict, normal, relaxed
VALIDATION_LEVEL=normal

# Auto-fix level: none, warnings, all
AUTO_FIX_LEVEL=none

# Notification settings
NOTIFICATION_ENABLED=true
NOTIFICATION_EMAIL=
NOTIFICATION_SLACK_WEBHOOK=
EOF

    success "Configuration created: $config_file"
    log "You can customize the validation settings by editing this file"
}

# Main execution
main() {
    local command="${1:-validate}"
    local target="${2:-$TEMPLATES_DIR}"

    log "Template Validation System"
    log "Project Root: $PROJECT_ROOT"
    log "Target: $target"
    echo

    case "$command" in
        "validate"|"--validate"|"-v")
            validate-template "$target"
            ;;
        "validate-all"|"--validate-all"|"-V")
            validate-all-templates "$target"
            ;;
        "monitor"|"--monitor"|"-m")
            local interval="${3:-300}"
            monitor-templates "$target" "$interval"
            ;;
        "config"|"--config"|"-c")
            create-validation-config
            ;;
        "help"|"--help"|"-h")
            echo "Template Validation Script"
            echo
            echo "Usage: $0 [COMMAND] [TARGET] [OPTIONS]"
            echo
            echo "Commands:"
            echo "  validate, -v     Validate a specific template (default)"
            echo "  validate-all, -V Validate all templates in directory"
            echo "  monitor, -m      Continuously monitor templates for contamination"
            echo "  config, -c       Create validation configuration file"
            echo "  help, -h         Show this help message"
            echo
            echo "Examples:"
            echo "  $0 validate templates/base-cpp"
            echo "  $0 validate-all templates/"
            echo "  $0 monitor templates/ 60    # Check every 60 seconds"
            echo "  $0 config"
            echo
            echo "This script ensures templates remain generic and free from"
            echo "domain-specific Moqui/DICOM/Monte Carlo code contamination."
            ;;
        *)
            error "Unknown command: $command"
            echo "Use '$0 --help' for usage information"
            exit 1
            ;;
    esac
}

# Run main function with all arguments
main "$@"
