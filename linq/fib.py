from linq import Quariable


def fib():
    prevprev = 1
    prev = 1
    yield prevprev
    yield prev
    while True:
        next = prev + prevprev
        yield next
        prevprev = prev
        prev = next


print(Quariable(fib())
      .where(lambda x: x % 3 == 0)
      .select(lambda x: x ** 2 if x % 2 == 0 else x)
      .take(5)
      .tolist())
