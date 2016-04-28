module Treap where
--Es una implementación (parcial) del TAD conjunto.
--Guarda un conjunto de keys
--A cada key le asigna una prioridad random.

--                 T prioridad left key right
data Treap a = E | T Int  (Treap a) a (Treap a) deriving Show

--Invariantes:
--Mirando las key, el treap es un arbol de busqueda
--Mirando las prioridades, el treap es un max-heap!

emptyT :: Treap a
emptyT = E

--mergea dos treaps, debe cumplirse que todas las key de l < las de r
--por lo tanto esta no es una funcion de mergeo general.
mergeT :: Treap a -> Treap a -> Treap a
mergeT E r = r
mergeT l E = l
mergeT l@(T lp ll lv lr) r@(T rp rl rv rr) | lp < rp = T lp ll lv (mergeT lr r)
                                           | otherwise = T rp (mergeT l rl) rv rr

--dado una key, parte un treap en dos segun una key.
--los de la izquierda tienen key menores, los de la derecha, mayores
splitT :: Ord a => Treap a -> a -> (Treap a, Treap a)
splitT E k = (E, E)
splitT (T p l v r) k | k<=v = let (l', r') = splitT l k
                              in (l', T p r' v r) 
                     | otherwise = let (l', r') = splitT r k
                                   in (T p l v l', r')
                                   
singletonT :: a -> Int -> Treap a
singletonT k elrandom = T elrandom E k E

insertT :: Ord a => Treap a -> a -> Int -> Treap a
insertT t k elrandom = mergeT (mergeT l (singletonT k elrandom)) r
    where (l, r) = splitT t k
    
--implementacion clasica, borra una key a lo BST
eraseT :: Ord a => Treap a -> a -> Treap a
eraseT (T p l v r) k | k==v = mergeT l r
                     | k<v  = T p (eraseT l k) v r
                     | k>v  = T p l v (eraseT r k)

--borra todas las keys en un rango... en O(log n) !! :O omg
erasesT :: Ord a => Treap a -> a -> a -> Treap a
erasesT t l r = mergeT t1 t4
        where (t1, t2) = splitT t l
              (t3, t4) = splitT t2 r
                

--Todas las operaciones son O(log n) (amortizado)
