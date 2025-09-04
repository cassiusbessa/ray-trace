# Organização dos Arquivos de Teste RT

Esta pasta contém todos os arquivos de cena (.rt) organizados por categoria:

## 📁 `valid/` - Cenas Válidas
Arquivos que devem renderizar corretamente sem erros:

- `green_blue_spheres.rt` - Cena com esferas verdes e azuis
- `multiple_spheres_with_patterns.rt` - Múltiplas esferas com padrões
- `zeze_ambient.rt` - Cena com cilindros e luz ambiente
- `test_ambient.rt` - Teste de iluminação ambiente
- `test_red_ambient.rt` - Teste de luz ambiente vermelha
- `test_correct.rt` - Cena de teste correta
- `test_single_sphere.rt` - Esfera única
- `test_simple.rt` - Cena simples
- `test_camera_fix.rt` - Teste de correção da câmera
- `test_fixed.rt` - Teste corrigido
- `test_final.rt` - Cena final
- `test_cilindro.rt` - Teste de cilindro
- `test_cylinder_specular.rt` - Cilindro com reflexão especular
- `test_specular_focus.rt` - Teste de foco especular
- `test_specular_simple.rt` - Reflexão especular simples
- `test_validation_demo.rt` - Demo de validação

## 📁 `invalid/` - Cenas com Erros
Arquivos que devem gerar erros de validação:

- `test_invalid_colors.rt` - Cores fora do range válido (0-255)
- `test_invalid_intensity.rt` - Intensidade inválida
- `test_invalid_ranges.rt` - Valores fora dos ranges permitidos
- `test_invalid_rgb_format.rt` - Formato RGB inválido
- `test_missing_params.rt` - Parâmetros faltando
- `test_extra_params.rt` - Parâmetros extras
- `test_zero_orientation.rt` - Orientação zero (inválida)
- `test_negative_diameter.rt` - Diâmetro negativo
- `test_custom_validation.rt` - Validação customizada

## Como usar

### Testar cenas válidas:
```bash
./miniRT scenes/valid/nome_da_cena.rt
```

### Testar validação com cenas inválidas:
```bash
./miniRT scenes/invalid/nome_da_cena.rt
```

As cenas inválidas devem retornar mensagens de erro específicas e não devem abrir a janela de renderização.
