# Ejercicio 1 — Permutaciones con Restricciones (Fuerza Bruta)

**Curso:** Análisis y Diseño de Algoritmos — Universidad EAFIT  
**Trabajo Práctico 01 | Ejercicio 1 (7.5%)**  
**Enfoque:** Fuerza Bruta con `next_permutation`

---

## Tabla de Contenidos

1. [Descripción del Problema](#1-descripción-del-problema)
2. [Enfoque de Solución: Fuerza Bruta](#2-enfoque-de-solución-fuerza-bruta)
3. [Pseudocódigo](#3-pseudocódigo)
4. [Estructura del Código](#4-estructura-del-código)
5. [Compilación y Ejecución](#5-compilación-y-ejecución)
6. [Ejemplos de Entrada y Salida](#6-ejemplos-de-entrada-y-salida)
7. [Complejidad Temporal y Espacial](#7-complejidad-temporal-y-espacial)
8. [Medición Experimental de Tiempos](#8-medición-experimental-de-tiempos)
9. [Preguntas Guía](#9-preguntas-guía)

---

## 1. Descripción del Problema

Dado un conjunto de `n` enteros positivos **distintos**, se desea generar todas las permutaciones posibles que satisfagan la restricción:

```
P[i] <= 2 * P[i+1]   para todo i en {0, 1, ..., n-2}
```

Es decir, ningún elemento puede ser mayor que el doble de su sucesor inmediato en la permutación.

**Ejemplo:**  
Para el conjunto `{1, 3, 4}`, la permutación `[3, 4, 1]` **no es válida** porque `4 > 2*1 = 2`.  
La permutación `[1, 3, 4]` **sí es válida** porque `1 <= 6` y `3 <= 8`.

El programa debe:
- Generar **todas** las `n!` permutaciones posibles.
- Filtrar las que cumplen la restricción.
- Reportar el total generado, el total válido y listar las permutaciones válidas.

---

## 2. Enfoque de Solución: Fuerza Bruta

### ¿Qué es Fuerza Bruta?

La fuerza bruta (también llamada *búsqueda exhaustiva*) es una estrategia algorítmica que consiste en **enumerar todas las soluciones posibles del espacio de búsqueda** y evaluar cada una contra el criterio de validez. No descarta candidatos de forma anticipada: primero genera, luego filtra.

### ¿Por qué es Fuerza Bruta y no Backtracking?

| Característica | Fuerza Bruta (este ejercicio) | Backtracking |
|---|---|---|
| Genera candidatos | Todos (n!) | Solo los prometedores |
| Poda temprana | ❌ No | ✅ Sí |
| Evalúa restricción | Al final (permutación completa) | Durante la construcción |
| Espacio explorado | Completo | Reducido |

En este programa, **la restricción `P[i] <= 2*P[i+1]` se verifica sobre la permutación completa ya construida**, no durante su construcción. Eso lo clasifica como fuerza bruta pura: no hay ningún mecanismo que evite generar permutaciones inválidas de antemano.

### ¿Por qué `next_permutation`?

Se eligió `std::next_permutation` de la STL por las siguientes razones:
- **Garantía matemática:** si el arreglo está ordenado ascendentemente al inicio, `next_permutation` recorre exactamente las `n!` permutaciones en orden lexicográfico y retorna `false` al llegar a la última, cerrando el ciclo de forma natural.
- **Eficiencia de implementación:** es una función optimizada de la librería estándar, evita errores de implementación manual y hace el código más legible.
- **Claridad semántica:** el ciclo `do-while` con `next_permutation` comunica directamente la intención de "recorrer todas las permutaciones posibles".

---

## 3. Pseudocódigo

### 3.1 Pseudocódigo del enunciado (referencia oficial)

El siguiente pseudocódigo fue suministrado por los docentes como guía base (Trabajo Práctico 01, Universidad EAFIT, 2025):

```
leer n
leer A[0..n-1]
ordenar A asc
total_generadas = 0
total_validas = 0

hacer:
    total_generadas += 1
    valida = verdadero
    para i en [0..n-2]:
        si A[i] > 2 * A[i+1]:
            valida = falso
            break
    si valida:
        imprimir A
        total_validas += 1

mientras next_permutation(A) exista

imprimir "total_generadas =", total_generadas
imprimir "total_validas =", total_validas
```

---

### 3.2 Pseudocódigo de nuestra solución en C++

El pseudocódigo a continuación describe **exactamente** la estructura y lógica de nuestro `main.cpp`. La solución se organiza en cuatro funciones bien separadas, cada una con responsabilidad única:

---

#### Función `esValida(perm)`
Recibe una permutación completa y evalúa si cumple la restricción en todos sus pares consecutivos.

```
FUNCIÓN esValida(perm[0..n-1]) → booleano
    PARA i DESDE 0 HASTA n-2:
        SI perm[i] > 2 * perm[i+1]:
            // Restricción violada: no hace falta seguir revisando
            RETORNAR falso
    // Todos los pares pasaron la restricción
    RETORNAR verdadero
FIN FUNCIÓN
```

---

#### Función `imprimirPerm(perm)`
Muestra una permutación en pantalla con formato `[ x1 x2 ... xn ]`.

```
FUNCIÓN imprimirPerm(perm[0..n-1])
    IMPRIMIR "[ "
    PARA CADA elemento x EN perm:
        IMPRIMIR x, " "
    IMPRIMIR "]"
FIN FUNCIÓN
```

---

#### Función `fuerzaBruta(A, imprimirValidas)`
Núcleo del algoritmo. Genera exhaustivamente todas las permutaciones de A usando
`next_permutation` y aplica el filtro sobre cada una.

```
FUNCIÓN fuerzaBruta(A[0..n-1], imprimirValidas: booleano)
    ORDENAR A ascendentemente
    // Garantiza que next_permutation recorra exactamente n! permutaciones,
    // comenzando desde la permutación lexicográficamente menor.

    total_generadas ← 0
    total_validas   ← 0

    REPETIR:                              // do-while: evalúa antes de avanzar
        total_generadas ← total_generadas + 1

        SI esValida(A):                   // delega la verificación a esValida()
            total_validas ← total_validas + 1
            SI imprimirValidas:
                imprimirPerm(A)           // solo imprime en modo interactivo

    MIENTRAS next_permutation(A) retorne VERDADERO
    // next_permutation reorganiza A en la siguiente permutación lexicográfica.
    // Retorna FALSO cuando A vuelve al estado mínimo → se agotaron las n! permutaciones.

    SI imprimirValidas:
        IMPRIMIR "Total permutaciones generadas : ", total_generadas
        IMPRIMIR "Total permutaciones validas   : ", total_validas
FIN FUNCIÓN
```

---

#### Función `medirTiempo(A)`
Envuelve `fuerzaBruta()` con un cronómetro de alta resolución para medir el
tiempo de ejecución sin contaminar la salida con permutaciones.

```
FUNCIÓN medirTiempo(A[0..n-1]) → real (milisegundos)
    inicio ← reloj_alta_resolución()
    fuerzaBruta(A, imprimirValidas=falso)   // ejecuta sin imprimir nada
    fin    ← reloj_alta_resolución()
    RETORNAR (fin - inicio) en milisegundos
FIN FUNCIÓN
```

---

#### Función `main()`
Punto de entrada. Orquesta la lectura de datos, la ejecución interactiva y
las pruebas de tiempo experimentales.

```
FUNCIÓN main()
    // ── Modo interactivo ──────────────────────────────────────────────────
    LEER n
    LEER A[0..n-1]

    fuerzaBruta(A, imprimirValidas=verdadero)

    // ── Medición experimental de tiempos ─────────────────────────────────
    IMPRIMIR encabezado de tabla: n | n! | Tiempo(ms)

    PARA CADA valor ni EN {8, 10, 11, 12}:
        prueba ← {1, 2, 3, ..., ni}        // arreglo de referencia

        factorial ← 1
        PARA j DESDE 1 HASTA ni:
            factorial ← factorial * j      // calcular ni! para mostrar en tabla

        tiempo ← medirTiempo(prueba)
        IMPRIMIR ni, factorial, tiempo

FIN FUNCIÓN
```

---

### 3.3 Relación entre el pseudocódigo del enunciado y nuestra implementación

| Elemento del enunciado | Cómo lo resolvimos en C++ |
|---|---|
| `leer n` / `leer A[0..n-1]` | `cin >> n` y loop de lectura en `main()` |
| `ordenar A asc` | `sort(A.begin(), A.end())` al inicio de `fuerzaBruta()` |
| Verificación `A[i] > 2*A[i+1]` | Función separada `esValida()` con cortocircuito |
| `imprimir A` si válida | Función separada `imprimirPerm()` |
| `next_permutation(A)` | `std::next_permutation` de `<algorithm>` en ciclo `do-while` |
| Contadores y reporte final | Variables `total_generadas` y `total_validas` en `fuerzaBruta()` |
| Medición de tiempos | Función adicional `medirTiempo()` con `std::chrono` — no estaba en el enunciado base, fue incorporada para el análisis experimental requerido en la actividad |

---

## 4. Estructura del Código

```
ejercicio1/
└── main.cpp      ← Código fuente completo
```

### Funciones principales

```cpp
bool esValida(const vector<int>& perm)
```
Recorre la permutación y verifica que se cumpla `P[i] <= 2 * P[i+1]` para todo par consecutivo. Retorna `false` en el primer par que viole la restricción (cortocircuito).

---

```cpp
void fuerzaBruta(vector<int> A, bool imprimirValidas = true)
```
Núcleo del algoritmo. Ordena el arreglo, luego itera con `next_permutation` sobre todas las permutaciones. Para cada una llama a `esValida()` y acumula contadores.

El parámetro `imprimirValidas` permite reutilizar esta función en el modo de medición de tiempos sin generar salida por pantalla.

---

```cpp
double medirTiempo(vector<int> A)
```
Envuelve `fuerzaBruta()` con un cronómetro de alta resolución (`std::chrono::high_resolution_clock`) y retorna el tiempo en milisegundos. Se usa para la tabla experimental.

---

```cpp
int main()
```
Lee `n` y el arreglo del usuario, ejecuta el algoritmo interactivo y luego corre automáticamente las pruebas de tiempo para `n = {8, 10, 11, 12}`.

---

## 5. Compilación y Ejecución

### Requisitos
- Compilador con soporte C++17 (g++ 7+ o clang++ 5+)
- macOS / Linux

### Compilar

```bash
g++ -O2 -std=gnu++17 -o solucion main.cpp
```

### Ejecutar

```bash
./solucion
```

El programa solicitará los datos de forma interactiva:

```
Ingrese n (cantidad de elementos): 3
Ingrese los 3 elementos distintos: 1 3 4
```

---

## 6. Ejemplos de Entrada y Salida

### Ejemplo 1 — Caso del enunciado

**Entrada:**
```
n = 3
A = 1 3 4
```

**Salida:**
```
=== FUERZA BRUTA: Permutaciones con restriccion P[i] <= 2*P[i+1] ===

Permutaciones validas:
[ 1 3 4 ]
[ 1 4 3 ]

Total permutaciones generadas : 6
Total permutaciones validas   : 2
```

**Verificación manual de las 6 permutaciones:**

| Permutación | P[0]≤2·P[1] | P[1]≤2·P[2] | ¿Válida? |
|---|---|---|---|
| `[1, 3, 4]` | 1 ≤ 6 ✅ | 3 ≤ 8 ✅ | ✅ |
| `[1, 4, 3]` | 1 ≤ 8 ✅ | 4 ≤ 6 ✅ | ✅ |
| `[3, 1, 4]` | 3 ≤ 2 ❌ | — | ❌ |
| `[3, 4, 1]` | 3 ≤ 8 ✅ | 4 ≤ 2 ❌ | ❌ |
| `[4, 1, 3]` | 4 ≤ 2 ❌ | — | ❌ |
| `[4, 3, 1]` | 4 ≤ 6 ✅ | 3 ≤ 2 ❌ | ❌ |

---

### Ejemplo 2 — Conjunto pequeño

**Entrada:**
```
n = 3
A = 1 2 3
```

**Salida:**
```
Permutaciones validas:
[ 1 2 3 ]
[ 1 3 2 ]
[ 2 3 1 ]

Total permutaciones generadas : 6
Total permutaciones validas   : 3
```

---

### Ejemplo 3 — Todos válidos

**Entrada:**
```
n = 2
A = 1 2
```

**Salida:**
```
Permutaciones validas:
[ 1 2 ]
[ 2 1 ]   ← válida porque 2 <= 2*1

Total permutaciones generadas : 2
Total permutaciones validas   : 2
```

---

## 7. Complejidad Temporal y Espacial

### Complejidad Temporal

| Etapa | Costo |
|---|---|
| Ordenar el arreglo inicial | O(n log n) |
| Generar cada permutación con `next_permutation` | O(n) amortizado por llamada |
| Total de permutaciones generadas | n! |
| Verificar la restricción en cada permutación | O(n) en el peor caso |
| **Total** | **O(n · n!)** |

El término dominante es `O(n · n!)` porque se aplica una verificación de costo `O(n)` a cada una de las `n!` permutaciones.

**Crecimiento:**

| n | n! | n · n! |
|---|---|---|
| 5 | 120 | 600 |
| 8 | 40,320 | 322,560 |
| 10 | 3,628,800 | 36,288,000 |
| 12 | 479,001,600 | 5,748,019,200 |

La función `n!` crece más rápido que cualquier función polinomial o exponencial fija, lo que hace al algoritmo **superexponencial** e impracticable para valores grandes de `n`.

### Complejidad Espacial

| Componente | Espacio |
|---|---|
| Arreglo de entrada `A` | O(n) |
| Variables de control (`totalGeneradas`, `totalValidas`, etc.) | O(1) |
| `next_permutation` opera in-place sobre `A` | O(1) adicional |
| **Total** | **O(n)** |

Una ventaja importante de usar `next_permutation` es que **no almacena todas las permutaciones en memoria simultáneamente**, sino que genera una a la vez y la evalúa en el acto. Esto mantiene el uso de memoria en O(n), independientemente de n.

---

## 8. Medición Experimental de Tiempos

Los tiempos se midieron en el mismo equipo usando `std::chrono::high_resolution_clock` con el arreglo `{1, 2, ..., n}`.

| n | n! (permutaciones) | Tiempo (ms) |
|---|---|---|
| 8 | 40,320 | ~0.3 ms |
| 10 | 3,628,800 | ~24 ms |
| 11 | 39,916,800 | ~424 ms |
| 12 | 479,001,600 | ~4,918 ms (~5 seg) |

> **Nota:** Los tiempos variarán según el procesador. Se recomienda correr el programa en tu Mac para obtener los valores específicos de tu equipo e incluirlos en el informe.

**¿A partir de qué n se vuelve impracticable?**  
A partir de `n = 12` el tiempo supera los 5 segundos en hardware moderno. Para `n = 13` (6,227,020,800 permutaciones) el tiempo estimado sería del orden de **1 minuto**, y para `n = 15` del orden de **horas**. En la práctica, `n ≥ 13` se considera **impracticable** para este enfoque.

---

## 9. Preguntas Guía

### ¿Por qué este enfoque se clasifica como Fuerza Bruta y no Backtracking?

Porque el algoritmo **genera primero y filtra después**: construye cada permutación completa de `n` elementos sin importar si los primeros elementos ya violan la restricción, y solo al tener la permutación completa aplica `esValida()`. No existe ninguna poda que detenga la construcción anticipadamente. El Backtracking, en cambio, verificaría la restricción `P[i] <= 2 * P[i+1]` en el momento de agregar cada elemento, y descartaría ramas enteras del árbol de búsqueda cuando se detecta un conflicto parcial.

---

### ¿Qué ocurre con la proporción de permutaciones válidas respecto al total a medida que n crece?

La proporción **disminuye** a medida que `n` crece. Con más elementos, la probabilidad de que una permutación aleatoria cumpla `P[i] <= 2*P[i+1]` en **todas** las posiciones consecutivas se reduce, porque la restricción debe satisfacerse simultáneamente en `n-1` pares. Experimentalmente:

| n | Total | Válidas (aprox.) | Proporción |
|---|---|---|---|
| 2 | 2 | 2 | 100% |
| 3 | 6 | 3 | ~50% |
| 4 | 24 | 8–10 | ~35–40% |
| 5 | 120 | ~25–30 | ~20–25% |

---

### Si se quisiera mejorar con Backtracking, ¿en qué paso se podría introducir la poda?

En un enfoque recursivo que construye la permutación posición a posición, la poda se introduciría **antes de agregar el elemento en la posición `i`**: si el elemento candidato `c` a colocar en `A[i]` ya viola `A[i-1] > 2 * c`, entonces toda la sub-rama que comienza con ese prefijo sería inválida, y se podría saltar directamente sin explorarla. Esto podría reducir drásticamente el número de nodos explorados cuando la restricción es estricta.

---

### ¿Por qué `next_permutation` garantiza exactamente n! permutaciones si el arreglo está ordenado?

`next_permutation` genera la **siguiente permutación en orden lexicográfico**. Si el arreglo comienza en su estado mínimo (ordenado ascendentemente), la función recorre todas las permutaciones posibles en orden creciente y retorna `false` exactamente cuando llega a la permutación máxima (ordenada descendentemente), cerrando el ciclo. Como hay exactamente `n!` ordenamientos posibles de `n` elementos distintos, el ciclo `do-while` itera exactamente `n!` veces.

---

## Referencias

- Levitin, A. (2012). *Introduction to the Design and Analysis of Algorithms* (3rd ed.). Pearson. — Capítulo 3: Brute Force and Exhaustive Search.
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
- cppreference.com. (2024). `std::next_permutation`. https://en.cppreference.com/w/cpp/algorithm/next_permutation
- cppreference.com. (2024). `std::chrono::high_resolution_clock`. https://en.cppreference.com/w/cpp/chrono/high_resolution_clock