from linq import Quariable
import re


FNAME = 'text.txt'

with open(FNAME, encoding='utf-8-sig') as f:
    print(Quariable(f)
          .select(lambda x: re.split('\\s', x.strip()))
          .flatten()
          .groupby(lambda x: x)
          .select(lambda x: (x[0], sum(1 for _ in x[1])))
          .orderby(lambda x: -x[1])
          .tolist()
          )
