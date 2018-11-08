import cv2 
import  matplotlib.pyplot as plt

def main():

	path = "10.png"

	img = cv2.imread(path,1)
	img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

	ret,thresh = cv2.threshold(gray,127,255,0)

	im2,counter,hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

	print (counter)
	print (hierarchy)
								#ALTERAR AQUI (0,0,0)
	cv2.drawContours(img,counter,-1,(0,0,255),2)

	original = cv2.imread(path,1)
	original = cv2.cvtColor(original,cv2.COLOR_BGR2RGB)

			#ALTERAR AQUI [original,IMG/THRESH]
	output = [original,img]
	titles = ['Original','Counter']

	for i in range(2):	
		plt.subplot(1,2,i+1)
		plt.imshow(output[i])
		plt.title(titles[i])
		plt.xticks([])
		plt.yticks([])
	plt.show()

if __name__=="__main__":
	main()
