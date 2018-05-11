import itertools


class Quariable(object):
    def __init__(self, iterable):
        self.iterable = iterable

    def select(self, selector):
        return Quariable(map(selector, self.iterable))

    def flatten(self):
        def gen(iterable):
            flow = iterable
            for seq in flow:
                for el in seq:
                    yield el
        return Quariable(gen(self.iterable))

    def where(self, filter_fn):
        return Quariable(filter(filter_fn, self.iterable))

    def take(self, k):
        def gen(iterable):
            n = 0
            for el in iterable:
                if n == k:
                    break
                n += 1
                yield el
        return Quariable(gen(self.iterable))

    def groupby(self, key):
        # elements must be sorted
        # so calling orderby first
        # https://stackoverflow.com/questions/20613507/itertools-groupby-not-grouping-unicode-string?lq=1
        return Quariable(itertools.groupby(self.orderby(key).iterable, key=key))

    def orderby(self, key):
        return Quariable(sorted(self.iterable, key=key))

    def tolist(self):
        return list(self.iterable)
