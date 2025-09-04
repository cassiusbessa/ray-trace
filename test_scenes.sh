#!/bin/bash

# Script para testar arquivos de cena RT
# Uso: ./test_scenes.sh [valid|invalid|all]

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "🎯 Ray Trace Scene Tester"
echo "========================="

# Função para testar arquivos válidos
test_valid_scenes() {
    echo -e "${YELLOW}Testing VALID scenes (should render successfully):${NC}"
    echo ""
    
    success_count=0
    total_count=0
    
    for file in scenes/valid/*.rt; do
        if [ -f "$file" ]; then
            filename=$(basename "$file")
            echo -n "Testing $filename... "
            
            # Roda o programa e captura apenas stderr para verificar se há erros
            if timeout 3s ./miniRT "$file" 2>/dev/null >/dev/null; then
                echo -e "${GREEN}✓ OK${NC}"
                ((success_count++))
            else
                echo -e "${RED}✗ FAILED${NC}"
            fi
            ((total_count++))
        fi
    done
    
    echo ""
    echo "Valid scenes: $success_count/$total_count passed"
}

# Função para testar arquivos inválidos
test_invalid_scenes() {
    echo -e "${YELLOW}Testing INVALID scenes (should fail with validation errors):${NC}"
    echo ""
    
    success_count=0
    total_count=0
    
    for file in scenes/invalid/*.rt; do
        if [ -f "$file" ]; then
            filename=$(basename "$file")
            echo -n "Testing $filename... "
            
            # Para arquivos inválidos, esperamos que o programa retorne erro
            if ! ./miniRT "$file" 2>/dev/null >/dev/null; then
                echo -e "${GREEN}✓ FAILED AS EXPECTED${NC}"
                ((success_count++))
            else
                echo -e "${RED}✗ SHOULD HAVE FAILED${NC}"
            fi
            ((total_count++))
        fi
    done
    
    echo ""
    echo "Invalid scenes: $success_count/$total_count failed as expected"
}

# Função para mostrar detalhes de um erro
show_error_details() {
    echo -e "${YELLOW}Error details for invalid scenes:${NC}"
    echo ""
    
    for file in scenes/invalid/*.rt; do
        if [ -f "$file" ]; then
            filename=$(basename "$file")
            echo -e "${YELLOW}=== $filename ===${NC}"
            ./miniRT "$file" 2>&1 || true
            echo ""
        fi
    done
}

# Parse argumentos da linha de comando
case "${1:-all}" in
    "valid")
        test_valid_scenes
        ;;
    "invalid")
        test_invalid_scenes
        ;;
    "errors")
        show_error_details
        ;;
    "all")
        test_valid_scenes
        echo ""
        test_invalid_scenes
        ;;
    *)
        echo "Usage: $0 [valid|invalid|errors|all]"
        echo "  valid   - Test only valid scenes"
        echo "  invalid - Test only invalid scenes"
        echo "  errors  - Show detailed error messages"
        echo "  all     - Test both valid and invalid scenes (default)"
        exit 1
        ;;
esac

echo ""
echo -e "${GREEN}Testing complete!${NC}"
