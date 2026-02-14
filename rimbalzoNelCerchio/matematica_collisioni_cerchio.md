# MATEMATICA DELLE COLLISIONI: PALLINA IN CERCHIO

**Riferimento completo per la simulazione**

---

## 📐 INDICE
1. Rilevare la collisione
2. Calcolare la normale
3. Riflessione della velocità
4. Correzione della posizione
5. Resistenza ed energia
6. Esempio numerico completo
7. Formule riassuntive

---

## 1️⃣ RILEVARE LA COLLISIONE

### Concetto Base
La pallina collide con il bordo del cerchio quando la distanza dal centro supera o eguaglia il **raggio del cerchio meno il raggio della pallina**.

### Dati
- **Centro cerchio:** C = (cx, cy)
- **Centro pallina:** P = (px, py)
- **Raggio cerchio:** R
- **Raggio pallina:** r

### Formula Distanza
```
d = √[(px - cx)² + (py - cy)²]
```

### Condizione di Collisione
```
d ≥ R - r
```

**Spiegazione:** Il centro della pallina può arrivare al massimo a distanza (R - r) dal centro del cerchio prima di toccare il bordo. Se d supera questo valore, c'è collisione.

**Visualizzazione:**
```
        ┌─────────────────┐
      ╱                     ╲
    ╱          C              ╲
   │         (cx,cy)           │  ← Cerchio grande (raggio R)
   │                           │
   │              ●            │
   │            P (○)          │  ← Pallina (raggio r) nel punto P
   │         d ←───→           │
    ╲                         ╱
      ╲                     ╱
        └─────────────────┘

Collisione quando: d ≥ R - r
```

---

## 2️⃣ CALCOLARE LA NORMALE

### Concetto
La **normale** n̂ è un vettore unitario (lunghezza = 1) perpendicolare alla superficie nel punto di contatto. Per un cerchio, punta sempre radialmente dal centro verso l'esterno.

### Vettore dal Centro alla Pallina
```
Δx = px - cx
Δy = py - cy
```

### Normalizzazione
```
nx = Δx / d
ny = Δy / d
```

dove d è la distanza calcolata prima.

**Proprietà:** nx² + ny² = 1 (vettore unitario)

**Significato geometrico:** n̂ = (nx, ny) indica la direzione in cui la "parete" spinge la pallina.

---

## 3️⃣ RIFLESSIONE DELLA VELOCITÀ

### Legge della Riflessione
Quando un oggetto urta una superficie:
- La componente **perpendicolare** alla superficie si inverte
- La componente **parallela** rimane invariata

### Scomposizione della Velocità

Data velocità **v** = (vx, vy):

**Prodotto scalare** (proiezione su normale):
```
v · n̂ = vx·nx + vy·ny
```

**Componente perpendicolare:**
```
v⊥ = (v · n̂) · n̂
```

In componenti:
```
v⊥x = (vx·nx + vy·ny) · nx
v⊥y = (vx·nx + vy·ny) · ny
```

**Componente parallela:**
```
v∥ = v - v⊥
```

### Formula della Riflessione (CHIAVE!)

La velocità riflessa è:
```
v' = v - 2·v⊥
```

Sostituendo:
```
v' = v - 2·(v · n̂)·n̂
```

**In componenti:**
```
v'x = vx - 2·(vx·nx + vy·ny)·nx
v'y = vy - 2·(vx·nx + vy·ny)·ny
```

### Forma Compatta
Definendo:
```
dot = vx·nx + vy·ny
```

Otteniamo:
```
v'x = vx - 2·dot·nx
v'y = vy - 2·dot·ny
```

**Questa è la formula finale da implementare!**

---

## 4️⃣ CORREZIONE DELLA POSIZIONE

### Problema
Durante l'aggiornamento discreto (frame-by-frame), la pallina può "affondare" oltre il bordo del cerchio.

### Calcolo della Penetrazione
```
penetrazione = d - (R - r)
```

Se penetrazione > 0, la pallina è andata troppo in là.

### Correzione
Sposta la pallina indietro lungo la normale:
```
px' = px - penetrazione · nx
py' = py - penetrazione · ny
```

**Nota:** Il segno negativo sposta la pallina verso l'interno del cerchio.

---

## 5️⃣ RESISTENZA ED ENERGIA

### Coefficiente di Restituzione
Per simulare perdita di energia, moltiplica la velocità riflessa per un coefficiente k:

```
0 < k ≤ 1
```

Valori tipici:
- k = 1.0 → rimbalzo perfettamente elastico (no perdita)
- k = 0.9 → rimbalzo realistico (10% perdita)
- k = 0.8 → rimbalzo con attrito
- k = 0.5 → pallina "morbida"

### Applicazione
```
v'x = k · v'x
v'y = k · v'y
```

### Soglia Minima
Per evitare micro-rimbalzi infiniti, ferma la pallina se troppo lenta:

```
se |v'x| < vmin → v'x = 0
se |v'y| < vmin → v'y = 0
```

Valore tipico: vmin = 0.5

---

## 6️⃣ ESEMPIO NUMERICO COMPLETO

### Dati Iniziali
- Centro cerchio: C = (500, 400)
- Raggio cerchio: R = 200
- Raggio pallina: r = 10
- Posizione pallina: P = (690, 400)
- Velocità: v = (5, 0) [si muove verso destra]
- Coefficiente resistenza: k = 0.9

### STEP 1: Calcola distanza
```
Δx = 690 - 500 = 190
Δy = 400 - 400 = 0

d = √(190² + 0²) = √36100 = 190
```

### STEP 2: Controlla collisione
```
d ≥ R - r ?
190 ≥ 200 - 10 ?
190 ≥ 190 → SÌ, COLLISIONE!
```

### STEP 3: Calcola normale
```
nx = 190 / 190 = 1.0
ny = 0 / 190 = 0.0

n̂ = (1, 0) ← punta verso destra
```

### STEP 4: Prodotto scalare
```
dot = vx·nx + vy·ny
dot = 5·1 + 0·0 = 5
```

### STEP 5: Riflessione
```
v'x = vx - 2·dot·nx = 5 - 2·5·1 = 5 - 10 = -5
v'y = vy - 2·dot·ny = 0 - 2·5·0 = 0

v' = (-5, 0) ← ora va verso sinistra!
```

### STEP 6: Resistenza
```
v'x = 0.9 · (-5) = -4.5
v'y = 0.9 · 0 = 0

v' finale = (-4.5, 0)
```

### STEP 7: Correzione posizione
```
penetrazione = 190 - 190 = 0

(In questo caso perfetta, nessuna correzione)
```

### Risultato Finale
- Nuova velocità: v = (-4.5, 0)
- Posizione: P = (690, 400) [già corretta]

La pallina ora rimbalza verso sinistra con velocità leggermente ridotta!

---

## 7️⃣ FORMULE RIASSUNTIVE

### Input
- P = (px, py) ← posizione pallina
- v = (vx, vy) ← velocità pallina
- C = (cx, cy) ← centro cerchio
- R ← raggio cerchio
- r ← raggio pallina
- k ← coefficiente resistenza (0.8 - 0.95)

### Algoritmo Completo

**1. Distanza**
```
d = √[(px - cx)² + (py - cy)²]
```

**2. Check collisione**
```
SE d ≥ R - r → COLLISIONE
```

**3. Normale**
```
nx = (px - cx) / d
ny = (py - cy) / d
```

**4. Prodotto scalare**
```
dot = vx·nx + vy·ny
```

**5. Riflessione**
```
v'x = vx - 2·dot·nx
v'y = vy - 2·dot·ny
```

**6. Resistenza**
```
v'x = k · v'x
v'y = k · v'y
```

**7. Correzione posizione**
```
penetrazione = d - (R - r)
px = px - penetrazione · nx
py = py - penetrazione · ny
```

**8. Soglia minima** (opzionale)
```
SE |v'x| < vmin → v'x = 0
SE |v'y| < vmin → v'y = 0
```

---

## 🎯 AGGIUNTE OPZIONALI

### Gravità
Tra un frame e l'altro, aggiungi:
```
vy = vy + g
```

Valori tipici: g = 0.2 - 0.5

### Attrito dell'aria
Riduci costantemente la velocità:
```
vx = vx · 0.99
vy = vy · 0.99
```

### Riduzione cerchio
Ad ogni collisione:
```
R = R - δR
```

dove δR = 1-5 pixel

### Cambio colore
Genera nuovo colore RGB casuale ad ogni collisione.

---

## 💡 INTUIZIONI CHIAVE

1. **Perché sottraggo 2·(v·n̂)·n̂?**
   - v·n̂ proietta la velocità sulla normale
   - Moltiplicando per n̂ ottengo il vettore v⊥
   - Il fattore 2 inverte e sottrae: v - 2v⊥ = v∥ - v⊥

2. **La normale è sempre radiale**
   - Per il cerchio, n̂ punta dal centro verso la pallina
   - Per altre forme (poligoni), serve calcolare diversamente

3. **Correzione posizione è cruciale**
   - Senza di essa, la pallina può "passare attraverso" il bordo
   - Specialmente con velocità alte o framerate bassi

4. **Resistenza simula realismo**
   - k = 1 → simulazione fisica ideale (irrealistico)
   - k < 1 → energia si dissipa come nel mondo reale

---

## 📚 RIFERIMENTI MATEMATICI

### Prodotto scalare
```
a · b = ax·bx + ay·by = |a|·|b|·cos(θ)
```

### Riflessione rispetto a un vettore
```
r = v - 2·(v·n̂)·n̂
```

### Normalizzazione vettore
```
û = u / |u|
dove |u| = √(ux² + uy²)
```

---

**Fine del documento**

Buona programmazione! 🚀
