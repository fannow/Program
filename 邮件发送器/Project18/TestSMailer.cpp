///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use SMailer.
// Written by Morning, mailto:moyingzz@etang.com
//
// Date:2003-5
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
#include "SMailer.h"
#include "WinSockHelper.h"

void main()
{
    MUtils::WinSockHelper wshelper;
    // make sure the file 'boot.ini' is in the root directory on driver C
    SMailer::TextPlainContent  content1("plain text content");
    SMailer::TextHtmlContent   content2("½ÐÎÒÒ»Éùµù");

	
    SMailer::MailInfo info;
    info.setSenderName("morning");
    info.setSenderAddress("185334690@qq.com");
    info.addReceiver("friend1", "1702959373@qq.com");
    info.addReceiver("friend2", "2252010028@qq.com");
    info.setPriority(SMailer::Priority::normal);
    info.setSubject("a test mail");
    info.addMimeContent(&content1);
    info.addMimeContent(&content2);

	
    try
    {
        SMailer::MailSender sender("smtp.qq.com", "185334690@qq.com", "ysidtuhpbiwxbhdg");
        SMailer::MailWrapper* v = new  SMailer::MailWrapper(&info);
        sender.setMail(v);
        sender.sendMail();
    }
    catch (SMailer::MailException& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unkown error" << std::endl;
    }
}