class Node:
    def __init__(self,pfn):
        self.pfn = pfn
        self.use = 0

class CacheClock:
    def __init__(self,size):
        self.cache = []
        self.hand = 0
    def insert(self,pfn):
        try:
            for i in range(len(cache)):
                if(pfn == cache[i].pfn):
                    cache[i].use = 1
                    return 0

            while(cache[hand].use != 0):
                cache[hand].use = 0
                hand = (hand + 1) % size
            
            replace = cache[hand].pfn
            cache[hand].
        except:


        