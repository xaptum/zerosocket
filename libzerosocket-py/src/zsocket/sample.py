import FileConfig
import zsocket
import time

def createConfig():
# No path then creates a file sock.conf. If path is given tries to read from the file
    conf = FileConfig.FileConfig()
    conf.set('ZUSR', 'xxx')
    conf.set('ZPAS', 'CirzntUlsrJh3aLnOWzPKA==')
    conf.set('ZDID', '46d86470-3202-11e4-92b6-42010af0f312')
    conf.set('ZADR', 'broker.xaptum.com')
    conf.set('ZPRT', 3301)
    conf.write()
    conf.close()

def send():
    conf = FileConfig.FileConfig('sock.conf')
    sock = zsocket.zsocket(conf)
    sock.connect()

    for i in range(0,4):
        time.sleep(0.028)
        sock.send("hello world")
    
#    buf = sock.recv(4096)
    sock.close()
#    print("received : %s", buf)

def main():
    createConfig()
    send()

if __name__ == "__main__":
    main()
