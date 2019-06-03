An utility that allows real-time processing of a Unity3d texture using a convolutional neural network. 

Original neural network https://github.com/mrharicot/monodepth

Original C++ monodepth implementation is here https://github.com/yan99033/monodepth-cpp

Dependencies: Tensorflow 1.6, OpenCV, Eigen, Protobuf

DepthToUnity: A shared library to connect the neural network with Unity3d. Can be used as a plugin.  

Unity_scripts: Contains the script MatRetriever.cs which mast be attached to the game object.

Note: requires GPU acceleration for high performance.

![Alt text](/preview.png?raw=true "Preview")

