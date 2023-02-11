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
				<img class="logo_img" alt="" src="static/img/logo.gif" >
				<div>
					<span>欢迎<span class="um_span">韩总</span>光临尚硅谷书城</span>
					<a href="../order/order.html">我的订单</a>
					<a href="../../index1.html">注销</a>&nbsp;&nbsp;
					<a href="../../index1.html">返回</a>
				</div>
		</div>
		
		<div id="main">
		
			<h1>欢迎回来 <a href="../../index1.html">转到主页</a></h1>
	
		</div>

		<%@include file="/page/common/login_menu.jsp"%>
</body>
</html>