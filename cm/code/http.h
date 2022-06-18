#ifndef __HTTP_H__
#define __HTTP_H__
#include<iostream>
#include<algorithm>
#include<string>
#include<sys/stat.h>
#include<vector>
#include<unistd.h>
#include<unordered_map>
#include<sys/sendfile.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include"until.h"
#include"socket.h"
#define WEBROOT "./webroot"
#define HOMEPATH "index.html"
#define VERSION "HTTP/1.0"
using namespace std;

/**
* http������
*/
class request {
private:
	int sock;
	string rq_line;              //������
	vector<string> rq_head;   //����ͷ
	string rq_space;           //�������
	string rq_body;            //������
private:
	//http������������
	string method;          //���󷽷�  get/post
	string version;			//http�汾��
	string uri;             //����·��

	unordered_map<string, string> headkv;  //kv��ʽ�������ͷ�������
	ssize_t rq_body_length;                 //�����峤��
	string path;                            //��Դ���·��
	string file_type;                       //������Դ����
	string query_string;                   //���ݵĲ���


	bool cgi;                             //����ǲ��ǿ�ִ���ļ�


public:
	request() {}
	request(int sock) :rq_space("\n"), file_type("text/html")
		, rq_body_length(-1), cgi(false), path(WEBROOT),sock(sock)
	{}
	void Run(int *mepoll);            //����http����
	void InsertLine(int *mepoll);		//��ȡ������;
	void RqLineParse();    //�������
	void RqHeadParse();    //����ͷ����
	void RqUriParse();     //����·������
	void RqUriPost();      //�޸�post������Դ����·��
	void InsertRqhead(int *mepoll);   //��ȡ����ͷ
	bool IsRecvRqBody();   //�Ƿ�Ҫ���������� postһ��Ҫ����������
	void InsertRqBody(int *mepoll);   //��ȡ������
	
	bool Method();         //���󷽷�����ǲ���post��get����

	bool IsGet();
	bool IsPost();
	void MakeSuff();

	ssize_t GetContextLength() { return rq_body_length; }
	string GetMethod() { return method; }
	string GetPath() { return path; }
	string Getquery() { return query_string; }
	bool GetCgi() { return cgi; }
	void SetCgi() { cgi = true; }
	void SetPath(string& path) { this->path= path; }
	string GetRqBody() { return rq_body; }
	string GetSuff() { return file_type; } //��ȡ�ļ�����
	
	void IsInsertIndex();
	~request() {}
};
//����http����Ѱ��������Դ·��
class Make {
private:
	request *re;
	string path;   //��Դ���·��
	int code;      //״̬��Ӧ��
	string suff;   //��Ӧ�ļ�����
	string ro_line;   //��Ӧͷ
	vector<string>  ro_head; //��Ӧͷ


	ssize_t file_size;					//�����ļ��ĵĴ�С---һ������Ӧ����
public:
    friend class response;
	Make() {}
	Make(request *re) :re(re) {}
	void Run();                         //������
	string MakeSuff(string suf);		//��ȡ�ļ���׺
	void MakeRoLineParse();
	void MakeRoLine();					//������Ӧ��
	void MakeRoHead();                  //������Ӧͷ
	ssize_t GetFileSize() { return file_size; }
	string GetRoLine() { return ro_line; }
	string CodetoStatus();                 //״̬������
	vector<string> GetRoHead() { return ro_head; }
	request*GetRequset() { return re; }
	
	~Make() {}
};



class response {
private:
	int sock;
	string resp_line;               //��Ӧ��
	vector<string> resp_head;		//��Ӧͷ
	string resp_space;				//��Ӧ����
	string resp_body;				//��Ӧ��
	Make *make=NULL;
	request *re=NULL;               
public:
	response() {}
	response(int sock,request *re, Make *make) :
	sock(sock),	re(re), make(make),resp_space("\r\n") {}
	void Run();
	void Cgi();
	void SendFiles();
};




/**
* ���󷽷�����
* 
*/
//����http����
void request::Run(int *mepoll) {
    InsertLine(mepoll);
    InsertRqhead(mepoll);
   

    //����ǲ���Ҫ����������
    if (IsRecvRqBody()) {
        InsertRqBody(mepoll);
    }
    /**
    * http��Ӧ�������
    */
    
}
void request::MakeSuff() {
    size_t pos = path.rfind('.');

    if (pos != string::npos) {
        file_type = path.substr(pos + 1);
    }
}
void request::InsertLine(int *mepoll) {
    string line;
    Sock::getline(sock, rq_line, mepoll);
    RqLineParse();//��������ͷ
}
void request::RqLineParse() {
    Util::StringParse(rq_line, method, uri, version);//�����з���
    LOG_INFO(LOG_ROOT()) << rq_line;
    LOG_INFO(LOG_ROOT()) << method;
    LOG_INFO(LOG_ROOT()) << uri;
    LOG_INFO(LOG_ROOT()) << version;
}
/**
* ��������ͷ��kvģʽ���뵽map��
* 
*/
void request::RqHeadParse() {
    for (auto& it : rq_head) {
        string k, v;
        Util::MakeStringKv(it, k, v);
        headkv.insert({ k,v });
        if (strcasecmp(k.c_str(), "Content-Length") == 0) {
            rq_body_length = atoi(v.c_str());//��������ͷ���ȷ����߶�ȡ������
        }
    }
}
/**
* ѭ����ȡ����ͷֱ����������Ϊֹ
*/
void request::InsertRqhead(int *mepoll) {
    while (1) {
    string strhead = "";
        Sock::getline(sock, strhead, mepoll);
     
        if (strhead.empty()) {
            break;
        }
        else {
            LOG_INFO(LOG_ROOT()) << strhead << endl;
            rq_head.push_back(strhead);
        }
    }
    //��ȡ��ֱ�ӽ�������ͷ

    RqHeadParse();
}
/**
* ����·������
* ����Դ·���Ͳ�������
*������һ��Ҫִ��cgi��cgi�����Ϊtrue
* ʣ��ľ�����Դ���·��
**/
void request::RqUriParse() {
    //����
    size_t pos = uri.find('?');
    if (pos != string::npos) {
        path += uri.substr(0, pos);
        query_string = uri.substr(pos + 1);
        //get����uri��߸��Ų���
       // ִ��cgi
        cgi = true;
    }
    else {
        path += uri;
    }

}
void request::RqUriPost() {
    path += uri;
}
bool request::IsRecvRqBody() {
    //���󷽷�Ϊpost���ܲ��������峤�ȴ���0ִ��cgi����
    if ((strcasecmp(method.c_str(), "post") == 0) && rq_body_length > 0) {
        //�ٱ�ͷ����Contxt-length--�����峤�Ȳ�Ϊ-1
        //post�������β�������������
        //Ҫִ��cgi
        cgi = true;
        return true;
    }
    return  false;
}
void request::InsertRqBody(int *mepoll) {
    ssize_t len = rq_body_length;
    char ch;
    string str = "";
    while (len) {
        int s = recv(sock, &ch, 1, 0);
        if (s < 0) {
            LOG_ERROR(LOG_ROOT()) << "recv request error" << endl;
        }
         else if (s == 0) {
            close(sock);
            epoll_ctl(*mepoll, EPOLL_CTL_DEL, sock, NULL);
            cout << "�ͻ��˹ر�" << endl;
        }
        str += ch;
        len--;
    }
    rq_body = str;
}
/**
* ����ǲ���post��get
*/
bool request::Method() {
    if ((strcasecmp(method.c_str(), "post") == 0) || (strcasecmp(method.c_str(), "get") == 0)) {
        return true;
    }
    return false;
    
}

void request::IsInsertIndex() {

    //��/��β/a/b/��β��Ҫ����
   //

    if (path[path.size() - 1] == '/') {
        path += HOMEPATH;
    }
}
/**
* �ǲ���get����
*/
bool request::IsGet() {
    if ((strcasecmp(method.c_str(), "get") == 0) ) {
        return true;
    }
    return false;
}
/**
* �ǲ���post����
*/
bool request::IsPost() {

        LOG_DEBUG(LOG_ROOT())<<"post"<<method<<endl;
    if ((strcasecmp(method.c_str(), "POST") == 0)) {
        return true;
    }
    return false;
}

/**
* ��������ʵ��
* 
*/

void Make::Run() {
    code = 200;
    //����ǲ���post����get������ֱ�������м����ֱ��������Ӧ
    if (!re->Method()) {
       LOG_WARN(LOG_ROOT()) << "request of method error"<<endl;
       goto end;
    }


    //����uri
    if (re->IsGet()) {
        re->RqUriParse();
    }
    else if(re->IsPost()) {
        re->RqUriPost();
    }
  
 //get������query_string��->��Դ��path����path���ݵĲ�����query_string��
 //post��ʽ��Դ��path�д��ݵĲ�������������

    //���path�ǲ���Ҫ������ҳ
    re->IsInsertIndex();

    path=re->GetPath();
    //���path�ǲ�����Ч·���ǲ�����webroot��Ŀ¼��
    struct stat st;
    //���path��Ч����st.st_mode�ĵ��ļ���Ӧ��ģʽ���ļ���Ŀ¼
    if (stat(path.c_str(), &st) < 0) {
        //�ļ�������·��


        LOG_WARN(LOG_ROOT()) << "path is html 404" << endl;;
        //      Log(WARNIG,"path is not html 404");
        code = 404;
    }
    else {
        //·������
        if (S_ISDIR(st.st_mode)) {
            //��ⷵ�ص��ǲ���·��
            LOG_DEBUG(LOG_ROOT()) << "path bug " << endl;
            //????����bugg
            //����/a/b��β�ĵ���b��һ��Ŀ¼
            path += "/";
            re->SetPath(path);
            re->IsInsertIndex();
            //����Ϊ/a/b/index.html 
        }
        else {
            if (S_IXUSR & st.st_mode || st.st_mode & S_IXOTH || st.st_mode & S_IXGRP) {
                //����ǲ��ǿ�ִ���ļ�
                  //ִ���ļ�����
                  //cgi����
                re->SetCgi();
            }
            else {
                //������html�ļ�
            }

        }

        if (!re->GetCgi()) {
            //����Ҫ���ؽ��
            file_size = st.st_size;//��ͨ�ļ�ֱ�������ļ���С

        }
    }
end:
    //������Ӧ��
    MakeRoLineParse();

    //������Ӧͷ
    MakeRoHead();
}
string Make::MakeSuff(string suff) {
    string su = "text/html";
    if (suff == "css") {
        su = "application/x-csi";
    }
    else if (suff == "html") {
        su = "text/html";
    }
    else  if (suff == "jpg") {
        su = "image/jpeg";
    }
    else if (suff == "jpe") {
        su = "image/jpeg";
    }
    else if (suff == "js") {
        su = "application/x-jpg";
    }

    return su;

}
void Make::MakeRoLineParse() {
    MakeRoLine();
}
void Make::MakeRoLine() {
    ro_line += VERSION;
    ro_line += " ";
    ro_line += to_string(code);
    ro_line += " ";
    ro_line += CodetoStatus();//codeת��Ϊ״̬��
    ro_line += "\r\n";
}
string Make::CodetoStatus() {
    string status = "";
    switch (code) {
    case 400:
        status = "fork you";
        break;
    case 404:
        status = "NOT FOUND";
        break;
    case 200:
        status = "OK";
        break;
    default:
        status = "OK";
        break;

    }
    return status;
}
/**
* ��Ӧͷ����
*/
void Make::MakeRoHead() {
    re->MakeSuff();
    string suff = re->GetSuff();
    string suff_ans = MakeSuff(suff);
    string suffparse = "Content-Type: ";
    suffparse += suff_ans;
    suffparse += "\r\n";
    LOG_DEBUG(LOG_ROOT()) << "repose head" << suffparse<<endl;
    ro_head.push_back(suffparse);
}
/**
* ��Ӧ����ʵ��
*/
void response::Run() {
    LOG_DEBUG(LOG_ROOT())<<"Run:"<<make->GetRequset()->GetMethod()<<endl;
    LOG_DEBUG(LOG_ROOT())<<"Run:"<<make->GetRequset()->GetRqBody()<<endl;
    LOG_DEBUG(LOG_ROOT())<<"Run:"<<re->GetRqBody()<<endl;
    resp_line = make->GetRoLine();
    resp_head = make->GetRoHead();
    resp_head.push_back(resp_space);

    //������Ӧ��
    int s = send(sock, resp_line.c_str(), strlen(resp_line.c_str()), 0);
    if (s < 0) {
        LOG_ERROR(LOG_ROOT()) << "resp_line send error" << endl;
    }
    for (auto& it : resp_head) {
        int c = send(sock, it.c_str(), strlen(it.c_str()), 0);
        if (c < 0) {
            LOG_ERROR(LOG_ROOT()) << "resp_head send error" << endl;
        }
    }
    //����ǲ����п�ִ���ļ�����ֱ�ӷ���������Դ
    if (re->GetCgi()) {
        //ִ�п�ִ���ļ�
        Cgi();
    }
    else {
        //����û�в���
      //���÷��ؽ��
      //ֱ�ӷ���������Դ
        SendFiles();
    }
}
void response::Cgi() {

    int pip_in[2] = { 0 };
    int pip_out[2] = { 0 };
    pipe(pip_in);
    pipe(pip_out);
    string path = re->GetPath();
    string method = re->GetMethod();
    string method_env = "METHOD=";//ͨ������������
    method_env += method;
    string query_string;
    string query_env;
    string content_length_env;
    string body;
    putenv((char*)method_env.c_str());//��method_env����ʽ���뵽ϵͳ���������������ӽ��̻�ȡ
    pid_t tid = fork();
    
    if (tid == 0) {
        //       �ӽ���ͨ��ֻд����
        close(pip_in[1]);
        close(pip_out[0]);
        dup2(pip_in[0], 0);//�ض���stdin��ȡ
        dup2(pip_out[1], 1);//�ض���stdoutд��
        //�������󷽷����ӽ���
          //һ����ͨ�������������ӽ���  ->GET�����ɸ����̸��ӽ��� ->uri���������query_string ��Ϊ��������
        if (re->IsGet()) {
            query_string = re->Getquery();

            query_env = "QUERY_STRING=";//ͨ������������
            query_env += query_string;
            putenv((char*)query_env.c_str());//��������������ϵͳ����������

        }
        else if (re->IsPost()) {
            content_length_env = "CONTENT-LENGTH=";
            content_length_env += to_string(re->GetContextLength());
            
            putenv((char*)content_length_env.c_str());
        }
        else {

        }
        //ִ�г��򽫽�����ظ�������
        //�����滻
        execl(path.c_str(), path.c_str(), NULL);
        exit(0);
    }
    close(pip_in[0]);
    close(pip_out[1]);
    //��һ����ͨ���ܵ����ݸ��ӽ��� ->POST�ɸ����̴��ݸ��ӽ��� ->  ������
    if (re->IsPost()) {
        LOG_DEBUG(LOG_ROOT())<<re->GetRqBody()<<endl;
        body = re->GetRqBody();
        //    ssize_t size=body.size();
        //    while(size){
        //      write(pip_in[1],&c,1);
         //     size--;
          //  }
        char ch = 'X';

        for (size_t i = 0;i < body.size();i++) {
            ch = body[i];
            write(pip_in[1], &ch, 1);

        }
    }
    char ch = 0;
    ssize_t s = 0;
    do {
        s = read(pip_out[0], &ch, 1);//��ȡ�ӽ��̷��صĽ��
        if (s > 0) {
            send(sock, &ch, 1, 0);//ֱ�ӷ����ӽ��̷��صĽ��
        }
    } while (s > 0);
    //���̵ȴ�
    waitpid(tid, NULL, 0);
    //close(pip_in[1]);
   // close(pip_out[0]);

}
void response::SendFiles() {
    LOG_INFO(LOG_ROOT()) << "file is sending";
       //�ȴ��ļ�
    string path =re->GetPath();
    int fd = open(path.c_str(), O_RDONLY);//ֻ����ʽ���ļ�

    if (fd < 0) {
        LOG_ERROR(LOG_ROOT()) << "open file is bug";
        return;
    }
    /**
    * ���ں�֮�䴫�����ݱ������ں˻��������û�������֮������ݿ�����Ч�ʺܸߣ�����Ϊ�㿽����
    */
    sendfile(sock, fd, NULL, make->GetFileSize());


    close(fd);
}

#endif // !__HTTP_H__