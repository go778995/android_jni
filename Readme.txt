这是一个包含JNI代码的android工程，用android stduio 建的工程，直接用android stduio打开工程并能编译过。


目前 native-lib.cpp 文件的int sent_socket()，里面的sendto函数返回-1，以及recv函数返回0，不知道为啥发送和接收都返回失败，有能帮我指导看看是什么问题，把sendt、recv收发调试成功，非常感谢。

另外这个sent_socket()函数，我在多个linux平台 centos、ubuntu等测试是没有没问题的。