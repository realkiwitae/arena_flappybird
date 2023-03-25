# Flappy arena

Simple neurovevolution in flappy bird custom arena

- structure adopted got no bias
- 3 - 6 - 1 layer sizes
- sigmoids with factor .1 between each layers
- input:
  a) fabs(x - pipe.x)
  b) fabs(y - gap.y + gap_w/2.f)
  c) fabs(y - gap.y - gap_w/2.f)
