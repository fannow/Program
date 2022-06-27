#ifndef __CONFIG_H__
#define __CONFIG_H__
#include<iostream>
#include<vector>
#include<string>
#include <typeinfo>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<memory>
#include<yaml-cpp/yaml.h>
#include<functional>
#include<sstream>//���л�
#include <boost/lexical_cast.hpp>
#include"../code/Log.h"
/*
 *ͨ�������ļ�����������
 *����ϵͳԭ�� Լ����������
 * */
using namespace std;
//����ϵͳyaml
//��������
class ConfigVarBase {
public:
	typedef shared_ptr<ConfigVarBase> ptr;
	ConfigVarBase(string name, string descripation = "") :
    m_name(name), m_description(descripation) {
      /*
       * ��Сдת����ת��Сд
       *
       * */
      transform(m_name.begin(),m_name.end(), m_name.begin(),::tolower);
    }
	virtual ~ConfigVarBase() {}
	string getname() { return m_name; };
	string getdescription() { return m_description; }

	virtual string Tostring() = 0;
	virtual bool fromstring(string val) = 0;
  virtual string getTypeName()=0;
protected:
	string m_name;
	string m_description;


};
//��������ת��������Fת��ΪT
//�����������ת��
template<class F,class T>
class LexicalCast{
  public:
    T operator()(F f){
      return boost::lexical_cast<T>(f);
    }
     
};
//����������ƫ�ػ�
template<class T>
class LexicalCast<string,vector<T>>{
  public:
   vector<T> operator()(string str){
     cout<<"vector  �����л�"<<endl;
     stringstream ss;
     //��yaml��ʽ��stringת��Ϊת��Ϊ������ʽ
      YAML::Node root=YAML::Load(str);//����ת��Ϊ����
      //ģ����ʵ����֮ǰ����֪��vector<T>��ʲô������ʹ��typename�����ö���ȷ������
      //typename�������͵ı��� ��һ�����Ͳ���һ��������
     typename   std::vector<T> vec;
      for(int i=0;i<root.size();i++){
        ss.str("");
        ss<<root[i];
        vec.push_back(LexicalCast<string,T>()(ss.str()));

      }
      return vec;
    }
     
};
//vector<T>�����л�
template<class T>
class LexicalCast<vector<T>,string>{
  public:
   string operator()(vector<T> &v){
     cout<<"vector  ���л�"<<endl;
     stringstream ss;
      YAML::Node root;
      for(auto &o:v){
        root.push_back(YAML::Load(LexicalCast<T,string >()(o)));
      }
      ss<<root;
      return ss.str();
    } 
     
};

//list������
template<class T>
class LexicalCast<string,list<T>>{
  public:
   list<T> operator()(string &str){
     stringstream ss;
     //��yaml��ʽ��stringת��Ϊת��Ϊ������ʽ
      YAML::Node root=YAML::Load(str);//����ת��Ϊ����
      //ģ����ʵ����֮ǰ����֪��list<T>��ʲô������ʹ��typename�����ö���ȷ������
      //typename�������͵ı��� ��һ�����Ͳ���һ��������
     typename   std::list<T> vec;
      for(int i=0;i<root.size();i++){
        ss.str("");
        ss<<root[i];
        vec.push_back(LexicalCast<string,T>()(ss.str()));

      }
      return vec;
    }
     
};
//list<T>�����л�
template<class T>
class LexicalCast<list<T>,string>{
  public:
   string operator()(list<T> &v){
     stringstream ss;
      YAML::Node root;
      for(auto &o:v){
        root.push_back(YAML::Load(LexicalCast<T,string >()(o)));
      }
      ss<<root;
      return ss.str();
    } 
};    
//set������
template<class T>
class LexicalCast<string,set<T>>{
  public:
   set<T> operator()(string &str){
     stringstream ss;
     //��yaml��ʽ��stringת��Ϊת��Ϊ������ʽ
      YAML::Node root=YAML::Load(str);//����ת��Ϊ����
      //ģ����ʵ����֮ǰ����֪��list<T>��ʲô������ʹ��typename�����ö���ȷ������
      //typename�������͵ı��� ��һ�����Ͳ���һ��������
     typename   std::set<T> vec;
      for(int i=0;i<root.size();i++){
        ss.str("");
        ss<<root[i];
        vec.insert(LexicalCast<string,T>()(ss.str()));

      }
      return vec;
    }
     
};
//set<T>�����л�
template<class T>
class LexicalCast<set<T>,string>{
  public:
   string operator()(set<T> &v){
     stringstream ss;
      YAML::Node root;
      for(auto &o:v){
        root.push_back(YAML::Load(LexicalCast<T,string >()(o)));
      }
      ss<<root;
      return ss.str();
    } 
};    
//unordered_set������
template<class T>
class LexicalCast<string,unordered_set<T>>{
  public:
   unordered_set<T> operator()(string &str){
     stringstream ss;
     //��yaml��ʽ��stringת��Ϊת��Ϊ������ʽ
      YAML::Node root=YAML::Load(str);//����ת��Ϊ����
      //ģ����ʵ����֮ǰ����֪��list<T>��ʲô������ʹ��typename�����ö���ȷ������
      //typename�������͵ı��� ��һ�����Ͳ���һ��������
     typename   std::unordered_set<T> vec;
      for(int i=0;i<root.size();i++){
        ss.str("");
        ss<<root[i];
        vec.insert(LexicalCast<string,T>()(ss.str()));

      }
      return vec;
    }
     
};
//unordered_set<T>�����л�
template<class T>
class LexicalCast<unordered_set<T>,string>{
  public:
   string operator()(unordered_set<T> &v){
     stringstream ss;
      YAML::Node root;
      for(auto &o:v){
        root.push_back(YAML::Load(LexicalCast<T,string >()(o)));
      }
      ss<<root;
      return ss.str();
    } 
};    
//map������
template<class T>
class LexicalCast<string,map<string,T>>{
  public:
   map<string,T> operator()(string str){
     //stringstream ss;
     //��yaml��ʽ��stringת��Ϊת��Ϊ������ʽ
      YAML::Node root=YAML::Load(str);//����ת��Ϊ����
      //ģ����ʵ����֮ǰ����֪��list<T>��ʲô������ʹ��typename�����ö���ȷ������
      //typename�������͵ı��� ��һ�����Ͳ���һ��������
     typename   std::map<string,T> vec;
     stringstream ss;
      for(auto it=root.begin();it!=root.end();it++){
        ss.str("");
        cout<<"size" <<typeid(*it).name();
       ss<<it->second;
      vec.insert(make_pair(it->first.Scalar(),LexicalCast<string,T>()(ss.str())));

      }
      return vec;
    }
     
};
//map<T>�����л�
template<class T>
class LexicalCast<map<string,T>,string>{
  public:
   string operator()(map<string,T> &v){
     stringstream ss;
      YAML::Node root;
      for(auto &o:v){
      root[o.first]=YAML::Load(LexicalCast<T,string >()(o.second));
      
      }
      ss<<root;
      return ss.str();
    } 
};    
//unordered_map������
template<class T>
class LexicalCast<string,unordered_map<string,T>>{
  public:
   unordered_map<string,T> operator()(string &str){
     stringstream ss;
     //��yaml��ʽ��stringת��Ϊת��Ϊ������ʽ
      YAML::Node root=YAML::Load(str);//����ת��Ϊ����
      //ģ����ʵ����֮ǰ����֪��list<T>��ʲô������ʹ��typename�����ö���ȷ������
      //typename�������͵ı��� ��һ�����Ͳ���һ��������
     typename   std::unordered_map<string,T> vec;
      for(auto it=root.begin();it!=root.end();it++){
        ss.str("");
        ss<<it->second;
        vec.insert(make_pair(it->first.Scalar(),LexicalCast<string,T>()(ss.str())));

      }
      return vec;
    }
     
};
//unordered_map<T>�����л�
template<class T>
class LexicalCast<unordered_map<string,T>,string>{
  public:
   string operator()(unordered_map<string,T> &v){
     stringstream ss;
      YAML::Node root;
      for(auto &o:v){
      root[o.first]=YAML::Load(LexicalCast<T,string >()(o.second));
      
      }
      ss<<root;
      return ss.str();
    } 
};
template<class T,class FormStr=LexicalCast<string,T>,class ToStr=LexicalCast<T,string>>
//�Զ�������ƫ�ػ�
class ConfigVar :public ConfigVarBase {
public:
	typedef shared_ptr<ConfigVar> ptr;
  //�ص�����  ��̬����-----���ø���ʱ֪ͨԭ����ֵ��ʲô���µ�ֵ��ʲô�������µ�ֵ��һЩ�ı�
  typedef std::function<void (const T &old_values,const T& new_value)>on_chang_ck;
 // map<uint64_t,on_chang_ck> m_ck;
  
	ConfigVar(string name, T& val, string description = "")
		: ConfigVarBase(name, description), m_val(val)
	{	}
	string Tostring() {
		try {
      return ToStr()(m_val);  
	//		using boost::lexical_cast;
			//��T ת��Ϊ��ʽstring
		//	return lexical_cast<string> (m_val);//��m_val��ʽ�����ص���׼�����ַ��������У�
			//Ȼ����Ϊģ��������������ģ��������string�����ǽ�m_valת��Ϊval���洢��string Ȼ����string��ʽ���أ�

		}
		catch (exception& e) {
			/*
			*e.what() ���쳣��Ϣ��ӡ����
			*typeid().name()�������������ر�������������
			*
			*/
			LOG_ERROR(LOG_ROOT()) << "ConfigVal::ToString expection" << e.what() << "convert:" << typeid(m_val).name() << "to string";
		}

	}
	bool fromstring(string val) override {
		try {
      setval(FormStr()(val));
      //		using boost::lexical_cast;
			//���ǽ�string����ת��Ϊģ��T
    //    return		m_val = lexical_cast<T>(val);//��m_val��ʽ�����ص���׼�����ַ��������У�
			//Ȼ����Ϊģ��������������ģ��������T�����ǽ�m_valת��Ϊval���洢��string Ȼ����T��ʽ���أ�
		}
		catch (exception& e) {
			/*
			*e.what() ���쳣��Ϣ��ӡ����
			*typeid().name()�������������ر�������������
			*
			*/
			LOG_ERROR(LOG_ROOT()) << "ConfigVal::ToString expection " << e.what() << " convert: string to" << typeid(m_val).name();
		}


	}
	T getval() { return m_val; cout<<"���ͣ���"<<typeid(m_val).name()<<endl;}
	void setval(T val) { 
    if(val==m_val){
      return;
    }
    //�ص�
    for(auto &o:m_ck){
      o.second(m_val,val);
    }
    m_val = val;
  }
  string getTypeName(){return typeid(T).name();}
  //���Ӽ���
  void AddListener(uint64_t key,on_chang_ck ck){

    m_ck[key]=ck;
  }
  //ɾ��
  void DelListener(uint64_t key){
    m_ck.erase(key);
  }
  //����������
 on_chang_ck GetChangCk(uint64_t key){
    auto  it=m_ck.find(key);
    return it==m_ck.end()?NULL:it->second;
  }
 void ClearListener(){
   m_ck.clear();
 }
private:
	T m_val;
  //��������飬�ص�����û�бȽϺ�����map�����ܹ�ͨ��key�Ƚϣ����һ�����ͨ��kryֱֵ��ɾ������ѡ��
  //uint64_t  key Ҫ��Ψһ   һ�����ʹ��hashֵ
 map<uint64_t,on_chang_ck> m_ck;
};


//���ù�����

class Config {
  public:
	typedef map<string, ConfigVarBase::ptr> ConfigValMap;
    static ConfigValMap &GetDatas(){
      static ConfigValMap s_datas;
      return s_datas;
    }
public:

template<class T>
	static  typename ConfigVar<T>::ptr LookUp(string name, T val, string description = "") {
    //������ͬ��ֵ
    //��ֹmap�г�����ͬ����ֱֵ�ӷ���
		auto tmp = GetDatas().find(name);
    if(tmp!=GetDatas().end()){
      auto cv=dynamic_pointer_cast<ConfigVar<T>>(tmp->second);//ǿ��ת��
  		if (cv) {
	  		LOG_INFO(LOG_ROOT()) << "LookUp name " << name << " exists";
		  	return cv;
      }else{
	  		LOG_ERROR(LOG_ROOT()) << "LookUp name " << name << " exists but type not "
          <<typeid(T).name()<<"type name="<<tmp->second->getTypeName()<<" "<<tmp->second->Tostring();
        return NULL;
      }
    }
		if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._12345678") != string::npos) {
			//���������ԭ�ַ����е�һ����ָ���ַ��������ַ����е���һ�ַ�����ƥ����ַ�����������λ�á�������ʧ�ܣ��򷵻�npos��
			LOG_ERROR(LOG_ROOT()) << "LookUp name invalid " << name;
				throw invalid_argument(name);//�׳���Ч����name
		}
		typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, val, description));
		GetDatas()[name] = v;
		return v;

	}
    template<class T>
	static typename   ConfigVar<T>::ptr LookUp(string name) {
		auto it = GetDatas().find(name);
		//û���ҵ�
		if (it == GetDatas().end()) {
			return nullptr;
		}
		//����ָ�������ת��  ������-->����
		//û������ָ��ʱ����dynamic_castת��
		return dynamic_pointer_cast<ConfigVar<T>> (it->second);

	}
  //���ҵ�ǰ��û����������
  //�о�ֱ�ӷ���
//��֮ǰ��Լ����������
 static  ConfigVarBase::ptr LookUpBase(string name){
  auto it=  GetDatas().find(name);  
  return it==GetDatas().end()?NULL:it->second;  
}
  //�����е�node��ӡ����
 static void ListAllMeber(string prefix,const YAML::Node node,list<pair<string,YAML::Node>> &output){
    //У�������Ƿ�Ϸ�

		if (prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._12345678") != string::npos) {
			LOG_ERROR(LOG_ROOT()) << "Config name invalid " << prefix<<":"<<node;
				return;
   }
    output.push_back(make_pair(prefix,node));
    if(node.IsMap()){
      for(auto it=node.begin();it!=node.end();it++){
          ListAllMeber(prefix.empty()?it->first.Scalar():prefix+"."+it->first.Scalar(),it->second,output);
        
      }
    }
  }
  
   static void LoadFormYaml(YAML::Node root){
     //����Ͳ���
    list<pair<string,YAML::Node>>all_node;
    //����node
    ListAllMeber("",root,all_node);
    //�������еĽṹ���Ƿ��һ�µ���һ����
    for(auto i:all_node){
      string key=i.first;
      if(key.empty()){
        continue;
      }
      //��Сдת��
      transform(key.begin(),key.end(),key.begin(),::tolower);
      ConfigVarBase::ptr val=LookUpBase(key);
      if(val){
        if(i.second.IsScalar()){
          val->fromstring(i.second.Scalar());
        }else {
          stringstream ss;
          ss<<i.second;
          val->fromstring(ss.str());  
        }
      }
    }
  }

};
#endif // !__CONIFIG_H__
