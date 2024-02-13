import tkinter as tk

class Window:
    def __init__(self, title = 'Prism Window', minsize = (200, 200), maxsize = (500, 500)):  
        self.title = title
        self.minsize = minsize
        self.maxsize = maxsize
        self.main()

    def main(self):
        root = tk.Tk()
        root.title(self.title)
        root.minsize(self.minsize)
        root.maxsize(self.maxsize)
        
        root.mainloop()




