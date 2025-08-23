# Recursive Subset Sum Trace

**Set**: `[1, 2, 3]`, **Target**: `3`

## Visual Decision Tree (Vertical Layout)

```
Start: index=0, sum=0, subset=[]
│
├─ Include 1? YES
│  │
│  ├─ index=1, sum=1, subset=[1]
│  │  │
│  │  ├─ Include 2? YES
│  │  │  │
│  │  │  ├─ index=2, sum=3, subset=[1,2]
│  │  │  │  │
│  │  │  │  └─ sum==3 ✅ PRINT [1,2]
│  │  │  
│  │  └─ Include 2? NO
│  │     │
│  │     ├─ index=2, sum=1, subset=[1]
│  │     │  │
│  │     │  ├─ Include 3? YES
│  │     │  │  │
│  │     │  │  └─ index=3, sum=4, subset=[1,3]
│  │     │  │     │
│  │     │  │     └─ sum>3 ❌ STOP
│  │     │  
│  │     │  └─ Include 3? NO
│  │     │     │
│  │     │     └─ index=3, sum=1, subset=[1]
│  │     │        │
│  │     │        └─ index>=3 ❌ STOP
│  
└─ Include 1? NO
   │
   ├─ index=1, sum=0, subset=[]
   │  │
   │  ├─ Include 2? YES
   │  │  │
   │  │  ├─ index=2, sum=2, subset=[2]
   │  │  │  │
   │  │  │  ├─ Include 3? YES
   │  │  │  │  │
   │  │  │  │  └─ index=3, sum=5, subset=[2,3]
   │  │  │  │     │
   │  │  │  │     └─ sum>3 ❌ STOP
   │  │  │  
   │  │  │  └─ Include 3? NO
   │  │  │     │
   │  │  │     └─ index=3, sum=2, subset=[2]
   │  │  │        │
   │  │  │        └─ index>=3 ❌ STOP
   │  │  
   │  └─ Include 2? NO
   │     │
   │     ├─ index=2, sum=0, subset=[]
   │     │  │
   │     │  ├─ Include 3? YES
   │     │  │  │
   │     │  │  └─ index=3, sum=3, subset=[3]
   │     │  │     │
   │     │  │     └─ sum==3 ✅ PRINT [3]
   │     │  
   │     │  └─ Include 3? NO
   │     │     │
   │     │     └─ index=3, sum=0, subset=[]
   │     │        │
   │     │        └─ index>=3 ❌ STOP
```

## Step-by-Step Execution

### Call 1: `find_subsets(set, 3, subset, 0, 0, 0, 3)`
- **Current state**: index=0 (looking at '1'), sum=0, subset=[]
- **Decision**: Should I include element at index 0 (which is '1')?
- **Action**: Try both options

### Call 2: `find_subsets(set, 3, subset, 1, 1, 1, 3)` [Include 1]
- **Current state**: index=1 (looking at '2'), sum=1, subset=[1]
- **Decision**: Should I include element at index 1 (which is '2')?
- **Action**: Try both options

### Call 3: `find_subsets(set, 3, subset, 2, 2, 3, 3)` [Include 1, Include 2]
- **Current state**: index=2 (looking at '3'), sum=3, subset=[1,2]
- **Check**: sum == target_sum (3) ✅
- **Action**: **PRINT [1, 2]** and return

### Call 4: `find_subsets(set, 3, subset, 1, 2, 1, 3)` [Include 1, Don't include 2]
- **Current state**: index=2 (looking at '3'), sum=1, subset=[1]
- **Decision**: Should I include element at index 2 (which is '3')?
- **Action**: Try both options

### Call 5: `find_subsets(set, 3, subset, 2, 3, 4, 3)` [Include 1, Don't include 2, Include 3]
- **Current state**: index=3, sum=4, subset=[1,3]
- **Check**: sum > target_sum (4 > 3) ❌
- **Action**: Return (stop this path)

### Call 6: `find_subsets(set, 3, subset, 1, 3, 1, 3)` [Include 1, Don't include 2, Don't include 3]
- **Current state**: index=3, sum=1, subset=[1]
- **Check**: index >= set_size (3 >= 3) ❌
- **Action**: Return (no more elements)

### Call 7: `find_subsets(set, 3, subset, 0, 1, 0, 3)` [Don't include 1]
- **Current state**: index=1 (looking at '2'), sum=0, subset=[]
- **Decision**: Should I include element at index 1 (which is '2')?
- **Action**: Try both options

### Call 8: `find_subsets(set, 3, subset, 1, 2, 2, 3)` [Don't include 1, Include 2]
- **Current state**: index=2 (looking at '3'), sum=2, subset=[2]
- **Decision**: Should I include element at index 2 (which is '3')?
- **Action**: Try both options

### Call 9: `find_subsets(set, 3, subset, 2, 3, 5, 3)` [Don't include 1, Include 2, Include 3]
- **Current state**: index=3, sum=5, subset=[2,3]
- **Check**: sum > target_sum (5 > 3) ❌
- **Action**: Return (stop this path)

### Call 10: `find_subsets(set, 3, subset, 1, 3, 2, 3)` [Don't include 1, Include 2, Don't include 3]
- **Current state**: index=3, sum=2, subset=[2]
- **Check**: index >= set_size ❌
- **Action**: Return

### Call 11: `find_subsets(set, 3, subset, 0, 2, 0, 3)` [Don't include 1, Don't include 2]
- **Current state**: index=2 (looking at '3'), sum=0, subset=[]
- **Decision**: Should I include element at index 2 (which is '3')?
- **Action**: Try both options

### Call 12: `find_subsets(set, 3, subset, 1, 3, 3, 3)` [Don't include 1, Don't include 2, Include 3]
- **Current state**: index=3, sum=3, subset=[3]
- **Check**: sum == target_sum (3) ✅
- **Action**: **PRINT [3]** and return

### Call 13: `find_subsets(set, 3, subset, 0, 3, 0, 3)` [Don't include 1, Don't include 2, Don't include 3]
- **Current state**: index=3, sum=0, subset=[]
- **Check**: index >= set_size ❌
- **Action**: Return

## Final Output
```
[1, 2]
[3]
```

## Key Pattern
Notice how the recursion **explores every possible combination**:
- [1,2,3] → sum=6 (too big)
- [1,2] → sum=3 ✅
- [1,3] → sum=4 (too big) 
- [1] → sum=1 (too small)
- [2,3] → sum=5 (too big)
- [2] → sum=2 (too small)
- [3] → sum=3 ✅
- [] → sum=0 (too small)

The recursion naturally generates all 2³ = 8 possible subsets and checks each one!