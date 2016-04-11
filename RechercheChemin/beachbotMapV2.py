# -*- coding: utf-8 -*-
"""
Created on Mon Apr 11 23:11:08 2016
@author: christianhamelain
"""
from carte import Map


size = (200, 300)

beachbotsForest = Map(size)




beachbotsForest.enclose(0)

# coins circulaires

beachbotsForest.popCircle((200,0),25,0)

beachbotsForest.popCircle((200,300),25,0)

# batons au sol

beachbotsForest.popRectangle((0,80),(20,83),0)

beachbotsForest.popRectangle((0,217),(20,220),0)



# # départ 1

# beachbotsForest.popRectangle((16,0),(16,8),0)

# beachbotsForest.popRectangle((24,0),(24,8),0)

# beachbotsForest.popRectangle((16,0),(24,1),0)

# # popcorn

# beachbotsForest.popRectangle((0,5),(2,7),0)

# beachbotsForest.popRectangle((0,11),(2,13),0)

# beachbotsForest.popRectangle((0,47),(2,49),0)

# beachbotsForest.popRectangle((0,53),(2,55),0)

# # marches

# beachbotsForest.popRectangle((0,19),(12,41),0)

# # estrade

# beachbotsForest.popRectangle((38,24),(40,36),0)

# # départ 2

# beachbotsForest.popRectangle((16,52),(16,60),0)

# beachbotsForest.popRectangle((24,52),(24,60),0)

# beachbotsForest.popRectangle((16,59),(24,60),0)


# beachbotsForest.enlargeYourPenis(3, -1)


beachbotsForest.displayForest()


