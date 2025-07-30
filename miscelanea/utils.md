## Convolución Binomial sobre Secuencia

### 📌 Problema
Dada una secuencia `x = [x₁, x₂, ..., xₙ]`, se reemplaza `x` por:
- `xᵢ ← xᵢ + xᵢ₊₁` (para cada i), durante `k` veces.

### ✅ Resultado
Después de `k` pasos, el elemento en la posición `i` es:

\[
x_i^{(k)} = \sum_{j=0}^{k} \binom{k}{j} \cdot x_{i + j}
\]

Para \( i = 1 \) hasta \( n - k \)

---
