
-- xs, '0' -> [xs, '0':xs, '1':xs]
-- xs, '1' -> [xs, '0':xs]

strs 0 = []
strs n = 
    strs' [""] n
    where 
        strs' xs 0 = xs
        strs' xs n' = 
            let xs0 = my_cat '0' xs
                xs1 = my_cat '1' xs
                xs' = concat [xs, xs0, xs1]
                xs'' = filter (\x -> x /= "") xs'
            in strs' xs'' (n' - 1)
        my_cat c sofar
            | c == '0' = map (c :) sofar
            | c == '1' = 
                let sofar' = 
                        filter (\x' -> case x' of 
                            [] -> True
                            x'@(c':cs) -> c' /= '1') sofar
                in map (c :) sofar'


cat_aggr xs = (concat . (map (\x -> map (++ x) xs))) xs

map_cat x = map (++ x)

main = do
    -- print $ map_cat "a" ["1", "2", "3"]
    print $ strs 4
