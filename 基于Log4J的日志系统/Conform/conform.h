#ifndef __CONFORM_H__
#define __CONFORM_H__
#include"../code/Log.h"
#include"../config/Config.h"


//����ϵͳ����־ϵͳ����
struct LogAppenderDefine {
    int type = 0;//��־�����  1  ������ļ� 2 ���������̨
    LogLevel::Level level = LogLevel::UNKNOW;
    string formater;//��־�����ʽ
    string file;
    bool operator==(const LogAppenderDefine& l)const {

        return type == l.type && level == l.level &&
            formater == l.formater && file == l.file;


    }
};


struct LogDefine {
    string name;
    LogLevel::Level level = LogLevel::UNKNOW;
    string formater;


    vector<LogAppenderDefine> addernders;

    bool operator==(const LogDefine& l)const {
        return name == l.name && level == l.level && formater == l.formater && addernders == l.addernders;
    }
    bool operator <(const LogDefine& l) const{

        return  name < l.name;

    }
};
//��־ϵͳ��ƫ�ػ�
template<>
class LexicalCast<string,set<LogDefine>>{
  public:
   set<LogDefine> operator()(string str){
     stringstream ss;
      YAML::Node root=YAML::Load(str);//����ת��Ϊ����
     typename   std::set<LogDefine> vec;
      for(size_t i=0;i<root.size();i++){
          auto it=root[i];
          if(!it["name"].IsDefined()){
            cout<<"log config error: name is null"<<it<<endl;
            continue;
          }
    
        LogDefine id;
        id.name=it["name"].as<string>();

        id.level=LogLevel::FormString(it["level"].IsDefined()?it["level"].as<string>(): "");
        if(it["formater"].IsDefined()){
          id.formater=it["formater"].as<string>();

        }
        if(it["addernders"].IsDefined()){
          for(size_t x=0;x<it["addernders"].size();x++){
            auto a=it["addernders"][x];
            LogAppenderDefine lad;
            if(!a["type"].IsDefined()){
            cout<<"log config error: appender is null"<<a<<endl;
              continue;
            }
            string type =a["type"].as<string>();
            if(type=="FileAppender"){
                lad.type=1;
                //��־�ļ�·��
                if(!a["file"].IsDefined()){
                          
                cout<<"log config error: file  is invaild"<<endl;
                continue;
                }
                lad.file=a["file"].as<string>();
              if(a["formater"].IsDefined()){
                lad.formater=a["formater"].as<string>();
               }
            }else if(type=="StdOutAppender"){
                lad.type=2;
            }else{
            cout<<"log config error: addernder type is invaild "<<type<<endl;
              continue;
            }
            id.addernders.push_back(lad);
          }       
        }
         vec.insert(id);

      }
      return vec;
    }
     
};
template<>
class LexicalCast<set<LogDefine>,string>{
  public:
   string operator()(set<LogDefine> &v){
     stringstream ss;
     YAML::Node root;
      for(auto &o:v){
      YAML::Node n;
      n["name"]=o.name;
      n["level"]=LogLevel::ToString(o.level);
      if(!o.formater.empty()){
        n["formater"]=o.formater;
      }
      for(auto &i:o.addernders){
        YAML::Node a;
        if(i.type==1){
            a["type"]="FileAppender";
            a["file"]=i.file;
        }else if(i.type==2){
          a["type"]="StdOutAppender";
        }
        a["level"]=LogLevel::ToString(i.level);   
         if(!i.formater.empty()){
          a["formater"]=i.formater;
         }
        n["addernders"].push_back(n);
       }
      root.push_back(n);
      }
      ss<<root;
      return ss.str();
   }
};

ConfigVar<set<LogDefine>>::ptr logdefine= Config::LookUp("logs", set<LogDefine>(), "logs config");
struct LogIniner {
    LogIniner(){
        logdefine->AddListener(0xABCDEF, [](const set<LogDefine>& old, const set<LogDefine>& nwe) {
            //����
            for (auto& o : nwe) {
                Logger::ptr logger;
                auto it = old.find(o);
                if (it == old.end()) {
                    //���ϵ���Ѱ�����û���ҵ�����ӵ�����
                    logger=LOG_NAME(o.name);            
                }
                else {
                    if (!(o == *it)) {
                        //�޸�logger
                        logger= LOG_NAME(o.name);//���ҵ���Ӧlogger
                    }
          
                }
                logger->SetLevel(o.level);
                if (!o.formater.empty()) {
                    logger->SetStringFormat(o.formater);     
                }

                logger->CleanAppender();
                for (auto& i : o.addernders) {
                    LogAppender::ptr ap;
                    if (i.type == 1) {
                        //����ļ����
                        ap.reset(new FileAppender(i.file.c_str()));
                    }
                    else if (i.type == 2) {
                        //��ӿ���̨���
                        ap.reset(new StdoutAppender());
                    }
                    //��������
                    //ʽ
        
                    if(!i.formater.empty()){
                      Formater::ptr fmt(new Formater(i.formater));
                      if(!fmt->IsError()){
                        ap->SetFormate(fmt);
                      }else{
                        cout<<"appender formater is inviled"<<endl;
                      }
                    }
                    ap->SetLevel(i.level);
                    logger->AddAppender(ap);

            }
                        //ɾ��  ------���µ����Ҳ����ϵľ�ɾ��
                        for (auto& i : old) {
                            auto it = nwe.find(i);
                            if (it == nwe.end()) {
                                auto logger = LOG_NAME(i.name);
                                logger->SetLevel((LogLevel::Level)100);
                                logger->CleanAppender();
                          }
                      }

                  }
        });
      }
            
   };//��־��ϵͳ��ʼ��
struct LogIniner _init_log;
#endif
