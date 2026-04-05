# Ejercicio 2 — Coloración de Grafos con k Colores (Backtracking)

**Curso:** Análisis y Diseño de Algoritmos — Universidad EAFIT  
**Docente:** Carlos Alberto Alvarez Henao  
**Estudiante 1:** Yan Frank Ríos López  
**Estudiante 2:** Juan Esteban Jiménez  
**Estudiante 3:** Juan José Garcia  
**Trabajo Práctico 01 | Ejercicio 2 (7.5%)**  
**Enfoque:** Backtracking y comparación con Fuerza Bruta

---

## Tabla de Contenidos

1. [Descripción del Problema](#1-descripción-del-problema)
2. [Enfoque de Solución: Backtracking](#2-enfoque-de-solución-backtracking)
3. [Pseudocódigo](#3-pseudocódigo)
4. [Estructura del Código](#4-estructura-del-código)
5. [Compilación y Ejecución](#5-compilación-y-ejecución)
6. [Ejemplos de Entrada y Salida](#6-ejemplos-de-entrada-y-salida)
7. [Complejidad Temporal y Espacial](#7-complejidad-temporal-y-espacial)
8. [Medición Experimental de Tiempos](#8-medición-experimental-de-tiempos)
9. [Preguntas Guía](#9-preguntas-guía)
10. [Referencias](#10-referencias)

---

## 1. Descripción del Problema

La **coloración de grafos** es un problema clásico de teoría de grafos que consiste en asignar colores a los vértices de un grafo de manera que **ningún par de vértices adyacentes comparta el mismo color**. Si esto se logra utilizando a lo sumo `k` colores, se dice que el grafo admite una **k-coloración válida**.

Este problema tiene aplicaciones reales en áreas como:
- **Asignación de frecuencias de radio**, donde transmisores cercanos no deben usar la misma frecuencia.
- **Horarios de exámenes**, evitando que estudiantes con materias en común presenten dos pruebas al mismo tiempo.
- **Registro de variables en compiladores**, asignando registros distintos a variables activas simultáneamente.

En este ejercicio se recibe:
- Un grafo no dirigido `G = (V, E)`.
- Un número de vértices `n`.
- Un número de colores disponibles `k`.
- Una **matriz de adyacencia** `adj[n][n]`, donde `adj[i][j] = 1` indica que existe una arista entre `i` y `j`, y `0` en caso contrario.

El programa debe:
- Determinar si existe al menos una `k`-coloración válida.
- Imprimir la **primera coloración válida encontrada**.
- Contar el **número total de k-coloraciones válidas**.
- Implementar una solución por **Fuerza Bruta** para comparar el conteo con el de Backtracking.
- Medir y comparar el tiempo de ejecución de ambos enfoques.

---

## 2. Enfoque de Solución: Backtracking

### ¿Qué es Backtracking?

El **Backtracking** es una estrategia algorítmica de búsqueda exhaustiva con poda. Construye la solución de forma incremental y, cuando detecta que una solución parcial ya no puede conducir a una solución válida, **abandona inmediatamente esa rama del árbol de búsqueda**.

En este ejercicio, el algoritmo asigna colores vértice por vértice:
1. Intenta asignar un color al vértice actual.
2. Verifica si esa asignación es segura, es decir, si ningún vecino ya coloreado tiene el mismo color.
3. Si la asignación es válida, continúa con el siguiente vértice.
4. Si no lo es, descarta esa opción y prueba otro color.
5. Cuando se han coloreado todos los vértices, se cuenta una solución válida.

### ¿Por qué es Backtracking y no Fuerza Bruta?

| Característica | Backtracking (este ejercicio) | Fuerza Bruta |
|---|---|---|
| Construcción de candidatos | Incremental | Completa |
| Poda temprana | ✅ Sí | ❌ No |
| Verifica restricciones | Durante la construcción | Al final |
| Espacio explorado | Reducido por conflictos | Completo |

En Backtracking, **la restricción se verifica en el momento de asignar cada color**. Si un color genera conflicto con un vecino adyacente, no se continúa explorando esa posibilidad. En la Fuerza Bruta, en cambio, se generan todas las `k^n` combinaciones posibles y solo al final se comprueba cuáles son válidas.

### ¿Por qué comparar con Fuerza Bruta?

La implementación por Fuerza Bruta sirve para:
- **Validar el conteo total** de soluciones encontrado por Backtracking.
- Mostrar empíricamente el beneficio de la poda.
- Comparar tiempos de ejecución sobre los mismos grafos.

---

## 3. Pseudocódigo

### 3.1 Pseudocódigo del enunciado (referencia oficial)

El siguiente pseudocódigo corresponde a la guía base suministrada en el enunciado del ejercicio:

```
leer n, k
leer matriz_ady[0..n-1][0..n-1] // 1 si hay arista, 0 si no
color[0..n-1] = 0 // 0 = sin color asignado
total_soluciones = 0
primera_guardada = falso

es_seguro(v, c):
 para cada u adyacente a v:
  si color[u] == c: retornar falso
 retornar verdadero

bt(v):
 si v == n:
  total_soluciones += 1
  si !primera_guardada:
   guardar color[]; primera_guardada = verdadero
  retornar

 para c en [1..k]:
  si es_seguro(v, c):
   color[v] = c
   bt(v + 1)
   color[v] = 0 // backtrack

bt(0)

si total_soluciones == 0:
 imprimir "No existe una", k, "-coloracion valida"
si no:
 imprimir "Total de", k, "-coloraciones:", total_soluciones
 imprimir "Primera solucion:", primera_solucion
```

---

### 3.2 Pseudocódigo de nuestra solución en C++

La solución implementada en C++ se organiza en funciones separadas para mantener claridad, reutilización y facilitar la comparación entre Backtracking y Fuerza Bruta.

---

#### Función `esSeguro(v, c)`
Verifica si el color `c` puede asignarse al vértice `v` sin entrar en conflicto con los vértices adyacentes ya coloreados.

```
FUNCIÓN esSeguro(v, c) → booleano
    PARA u DESDE 0 HASTA n-1:
        SI matriz_ady[v][u] == 1 Y color[u] == c:
            RETORNAR falso
    RETORNAR verdadero
FIN FUNCIÓN
```

---

#### Función `backtracking(v)`
Asigna colores recursivamente, vértice por vértice, contando soluciones válidas y guardando la primera encontrada.

```
PROCEDIMIENTO backtracking(v)
    SI v == n:
        totalBT ← totalBT + 1
        SI no se ha guardado la primera solución:
            guardar color[] en primeraSolucionBT[]
        RETORNAR

    PARA c DESDE 1 HASTA k:
        SI esSeguro(v, c):
            color[v] ← c
            backtracking(v + 1)
            color[v] ← 0
FIN PROCEDIMIENTO
```

---

#### Función `esValidaCompleta(asignacion)`
Valida una asignación completa usada en Fuerza Bruta.

```
FUNCIÓN esValidaCompleta(asignacion[0..n-1]) → booleano
    PARA i DESDE 0 HASTA n-1:
        PARA j DESDE i+1 HASTA n-1:
            SI matriz_ady[i][j] == 1 Y asignacion[i] == asignacion[j]:
                RETORNAR falso
    RETORNAR verdadero
FIN FUNCIÓN
```

---

#### Función `fuerzaBruta(pos)`
Genera todas las `k^n` asignaciones posibles y valida solo cuando la asignación está completa.

```
PROCEDIMIENTO fuerzaBruta(pos)
    SI pos == n:
        SI esValidaCompleta(colorFB):
            totalFB ← totalFB + 1
            SI no se ha guardado la primera solución:
                guardar colorFB[] en primeraSolucionFB[]
        RETORNAR

    PARA c DESDE 1 HASTA k:
        colorFB[pos] ← c
        fuerzaBruta(pos + 1)
FIN PROCEDIMIENTO
```

---

#### Función `main()`
Lee el grafo, ejecuta ambos enfoques, imprime resultados y tiempos, y permite comparar el conteo total.

```
FUNCIÓN main()
    LEER n
    LEER k
    LEER matriz de adyacencia

    inicializar estructuras de Backtracking y Fuerza Bruta

    medir tiempo de backtracking
    ejecutar backtracking(0)

    medir tiempo de fuerza bruta
    ejecutar fuerzaBruta(0)

    imprimir primera solución de Backtracking si existe
    imprimir totalBT
    imprimir totalFB
    imprimir verificación de conteo
    imprimir nodos explorados
    imprimir tiempos
FIN FUNCIÓN
```

---

### 3.3 Relación entre el pseudocódigo del enunciado y nuestra implementación

| Elemento del enunciado | Cómo lo resolvimos en C++ |
|---|---|
| `leer n, k` | `cin >> n >> k` en `main()` |
| `leer matriz_ady` | Lectura de matriz con `vector<vector<int>>` |
| `color[ ] = 0` | Vectores inicializados en el constructor |
| `es_seguro(v, c)` | Función `isSafe(int v, int c)` |
| `bt(v)` | Función recursiva `backtracking(int v)` |
| Guardar primera solución | Vector `firstSolutionBT` y bandera `firstSavedBT` |
| Contar soluciones | Variable `totalBT` |
| Comparación con fuerza bruta | Función recursiva `bruteForce(int pos)` |
| Medición de tiempo | `std::chrono::high_resolution_clock` |

---

## 4. Estructura del Código

```
ejercicio2/
└── main.cpp      ← Código fuente completo
```

### Funciones principales

```cpp
bool isSafe(int v, int c)
```
Verifica si el color `c` puede asignarse al vértice `v` sin entrar en conflicto con sus vértices adyacentes.

---

```cpp
void backtracking(int v)
```
Implementa el algoritmo principal de Backtracking. Recorre los vértices, intenta asignarles colores válidos, cuenta el total de soluciones y guarda la primera.

---

```cpp
bool isValidFullAssignment(const vector<int>& assignment)
```
Revisa si una asignación completa de colores es válida. Se usa en el enfoque de Fuerza Bruta.

---

```cpp
void bruteForce(int pos)
```
Genera todas las `k^n` combinaciones posibles de colores y utiliza `isValidFullAssignment()` para contar las válidas.

---

```cpp
void solveAndPrint()
```
Ejecuta ambos algoritmos, mide tiempos, imprime la primera solución encontrada, el total de soluciones, la verificación de conteo, los estados explorados y los tiempos.

---

```cpp
int main()
```
Lee `n`, `k` y la matriz de adyacencia; luego crea el objeto solucionador y llama a `solveAndPrint()`.

---

## 5. Compilación y Ejecución

### Requisitos
- Compilador con soporte C++17 (g++ 7+ o clang++ 5+)
- macOS / Linux / Windows con MinGW o WSL

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
Ingrese numero de vertices n: 4
Ingrese numero de colores k: 3
Ingrese la matriz de adyacencia (4x4):
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
```

---

## 6. Ejemplos de Entrada y Salida

Se presentan tres casos de prueba: uno tomado del enunciado, uno donde existe coloración válida en un grafo completo pequeño, y uno donde no existe solución para el valor de `k` dado.

---

### Ejemplo 1 — Ciclo `C4` con `k = 3`

**Propósito:** Verificar el caso de referencia del enunciado y confirmar el conteo total de coloraciones.

**Entrada:**
```
Ingrese numero de vertices n: 4
Ingrese numero de colores k: 3
Ingrese la matriz de adyacencia (4x4):
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
```

**Salida esperada:**
```
===== RESULTADOS =====
Total de 3-coloraciones (Backtracking): 18
Primera solucion encontrada por Backtracking:
color[0] = 1
color[1] = 2
color[2] = 1
color[3] = 2

Fuerza Bruta confirma: 18
Verificacion de conteo: COINCIDE
```

**Justificación:** Para el ciclo `C4` con `k = 3`, el número total de coloraciones válidas es 18. La primera solución depende del orden de exploración, pero la mostrada arriba es la primera encontrada cuando se prueban colores en orden ascendente.

---

### Ejemplo 2 — Grafo completo `K3` con `k = 3`

**Propósito:** Probar un caso donde cada vértice debe tener un color distinto.

**Entrada:**
```
Ingrese numero de vertices n: 3
Ingrese numero de colores k: 3
Ingrese la matriz de adyacencia (3x3):
0 1 1
1 0 1
1 1 0
```

**Salida esperada:**
```
===== RESULTADOS =====
Total de 3-coloraciones (Backtracking): 6
Primera solucion encontrada por Backtracking:
color[0] = 1
color[1] = 2
color[2] = 3

Fuerza Bruta confirma: 6
Verificacion de conteo: COINCIDE
```

**Justificación:** En `K3`, cada uno de los tres vértices debe tener un color distinto. El número de coloraciones válidas es `3 * 2 * 1 = 6`.

---

### Ejemplo 3 — Grafo completo `K3` con `k = 2`

**Propósito:** Mostrar un caso sin solución.

**Entrada:**
```
Ingrese numero de vertices n: 3
Ingrese numero de colores k: 2
Ingrese la matriz de adyacencia (3x3):
0 1 1
1 0 1
1 1 0
```

**Salida esperada:**
```
===== RESULTADOS =====
No existe una 2-coloracion valida.

Fuerza Bruta confirma: 0
Verificacion de conteo: COINCIDE
```

**Justificación:** Un triángulo no puede colorearse con solo 2 colores, porque cada vértice es adyacente a los otros dos.

---

## 7. Complejidad Temporal y Espacial

### Complejidad Temporal

#### Fuerza Bruta

| Etapa | Costo |
|---|---|
| Generar todas las asignaciones posibles | `k^n` |
| Validar cada asignación completa | `O(n^2)` |
| **Total** | **O(k^n · n^2)** |

En Fuerza Bruta, se generan todas las combinaciones posibles de colores para los `n` vértices y cada una se revisa al final.

#### Backtracking

| Etapa | Costo |
|---|---|
| Intentar colores por vértice | hasta `k` por nivel |
| Verificar seguridad por intento | `O(n)` |
| **Peor caso** | **O(k^n · n)** |

Aunque el peor caso sigue siendo exponencial, Backtracking reduce significativamente el espacio explorado en la práctica gracias a la poda temprana.

### Complejidad Espacial

| Componente | Espacio |
|---|---|
| Matriz de adyacencia | `O(n^2)` |
| Arreglos de colores y soluciones | `O(n)` |
| Pila recursiva | `O(n)` |
| **Total** | **O(n^2)** |

---

## 8. Medición Experimental de Tiempos

Los tiempos deben medirse en el mismo equipo usando `std::chrono::high_resolution_clock`. Se recomienda probar al menos dos grafos diferentes para comparar la efectividad de la poda.

### Tabla sugerida para el informe

| Grafo | n | k | Total soluciones | Estados BT | Estados FB | Tiempo BT | Tiempo FB |
|---|---:|---:|---:|---:|---:|---:|---:|
| Ciclo `C4` | 4 | 3 | 18 | menor | mayor | menor | mayor |
| Completo `K4` | 4 | 3 | 0 | mucho menor | mayor | mucho menor | mayor |

### Observaciones esperadas

- En grafos con muchas aristas, la poda de Backtracking resulta más efectiva porque los conflictos aparecen temprano.
- En grafos con pocas aristas, Backtracking se acerca más al comportamiento de Fuerza Bruta.
- La Fuerza Bruta siempre recorre todo el espacio de búsqueda, mientras que Backtracking solo expande ramas prometedoras.

> **Nota:** Los tiempos exactos dependen del computador, el compilador y las opciones de optimización utilizadas. Por eso deben reportarse los valores obtenidos experimentalmente por el grupo.

---

## 9. Preguntas Guía

### ¿Cuántos nodos explora el Backtracking vs la Fuerza Bruta en el ejemplo anterior? Justifique.

Para el caso del ciclo `C4` con `k = 3`, la Fuerza Bruta recorre todas las combinaciones posibles. Esto implica explorar el árbol completo de profundidad 4 con factor de ramificación 3, es decir, `3^4 = 81` asignaciones completas, o `1 + 3 + 9 + 27 + 81 = 121` nodos si se cuentan todos los estados del árbol.

Backtracking explora menos nodos, porque corta las ramas en cuanto detecta un conflicto entre vértices adyacentes. Por eso, el número de estados recorridos por Backtracking siempre será menor o igual al de Fuerza Bruta, y puede observarse exactamente con el contador `nodesBT` implementado en el programa.

---

### ¿Qué tipo de grafo maximizaría el efecto de la poda en el Backtracking? ¿Y cuál lo minimizaría?

La poda se maximiza en **grafos densos**, especialmente en grafos completos o casi completos, porque las restricciones son muchas y los conflictos aparecen muy temprano.

La poda se minimiza en **grafos dispersos**, como el grafo vacío o grafos con muy pocas aristas, porque casi cualquier asignación parcial sigue siendo válida y el algoritmo se comporta de forma muy parecida a Fuerza Bruta.

---

### ¿Qué cambio se debe hacer al algoritmo si solo se quiere saber si existe al menos una k-coloración, sin contar todas?

Debe modificarse el algoritmo para que **retorne inmediatamente al encontrar la primera solución válida**. Es decir, en lugar de seguir explorando para contar todas las coloraciones, la función recursiva debe devolver `true` tan pronto como llegue al caso base `v == n`, y propagar ese valor para terminar toda la búsqueda.

---

### Investigue: ¿Qué relación existe entre este problema y el Número Cromático del grafo?

El **número cromático** de un grafo, denotado `χ(G)`, es el menor número de colores necesario para colorear válidamente sus vértices.

La relación con este ejercicio es directa:
- Si el grafo admite una `k`-coloración, entonces `χ(G) ≤ k`.
- Si no admite una `k`-coloración, entonces `χ(G) > k`.

Por tanto, el problema de decidir si existe una `k`-coloración válida equivale a preguntar si `k` es al menos tan grande como el número cromático del grafo.

---

## 10. Referencias

- Levitin, A. (2012). *Introduction to the Design and Analysis of Algorithms* (3rd ed.). Pearson.
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
- Bondy, J. A., & Murty, U. S. R. (2008). *Graph Theory*. Springer.
- Rosen, K. H. (2012). *Discrete Mathematics and Its Applications* (7th ed.). McGraw-Hill.
- cppreference.com. (2024). `std::chrono::high_resolution_clock`. https://en.cppreference.com/w/cpp/chrono/high_resolution_clock

