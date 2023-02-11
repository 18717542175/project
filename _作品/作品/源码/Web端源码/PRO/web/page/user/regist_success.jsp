<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>智慧果园管家</title>
	<base href="http://localhost:8080/pro/"/>
	<%@include file="/page/common/head.jsp"%>
<style type="text/css">
	h1 {
		text-align: center;
		margin-top: 200px;
	}
	
	h1 a {
		color:red;
	}
</style>
</head>
<body>
		<div id="header">

		</div>
		
		<div id="main">
		
			<h1>注册成功! <a href="fristPage.jsp">转到主页</a></h1>
	
		</div>

		<%--使用静态包含--%>
		<%@include file="/page/common/login_menu.jsp"%>
</body>
</html>