<%--
  Created by IntelliJ IDEA.
  User: hangover
  Date: 2021/12/29
  Time: 21:29
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
    <title>head</title>
    <base href="http://localhost:8080/pro/"/>
</head>
<%
    //获取服务器的Ip地址
    String basePath = request.getScheme() //请求方式
            + "://"
            +request.getServerName() //Ip地址
            +":"
            +request.getServerPort()   //端口号
            +request.getContextPath()      //工程路径
            +"/";
%>
<body>
    <!--	写base标签 永远固定相对路径跳转的结果-->
    <base href="<%=basePath%>">
    <link type="text/css" rel="stylesheet" href="page/static/css/style.css" >
    <script type="text/javascript" src="lib/jquery-1.7.2.js"></script>
</body>
</html>
