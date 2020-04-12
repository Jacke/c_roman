#!/usr/bin/env python

import classes

t = classes.World()
t.set("fuck off!")
print (t.greet())

t.many(['Good Morning', 'Buon giorno', 'Kali mera'])
print (t.greet())


