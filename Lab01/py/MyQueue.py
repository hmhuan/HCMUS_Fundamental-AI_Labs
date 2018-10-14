class PriorityQueue:
    def __init__(self):
        self.Q = []
    def put(self, item):
        self.Q.append(item)
        id = len(self.Q) - 1
        while (id > 0) and (self.Q[id] < self.Q[int(id/2)]) :
            temp = self.Q[id]
            self.Q[id] = self.Q[int(id/2)]
            self.Q[int(id/2)] = temp
            id = int(id/2)
        # for i in range(len(self.Q)):
        #     print(self.Q[i],end=" ")
        # print()
    def __getitem__(self, id):
        return self.Q[id]
    def get(self):
        val = self.Q[0]
        self.Q.pop()
        if (len(self.Q) != 0):
            n, id = len(self.Q) - 1, 0
            self.Q[0] = self.Q[n]
            while (id * 2 + 1 <= n and self.Q[id] > self.Q[id * 2 + 1]) or (id * 2 + 2 <= n and self.Q[id] > self.Q[id *2 + 2]):
                temp = self.Q[id]
                if (self.Q[id * 2 + 1] < self.Q[id * 2 + 2]):
                    self.Q[id] = self.Q[id * 2 + 1]
                    id = id * 2 + 1 
                    self.Q[id] = temp
                else:
                    self.Q[id] = self.Q[id * 2 + 2]
                    id = id * 2 + 2
                    self.Q[id] = temp
            
        return val
    def _print(self):
        for i in range(len(self.Q)):
            print(self.Q[i], end=" ")
        print()
    def empty(self):
        return (len(self.Q) == 0)
    def size(self):
        return len(self.Q)




