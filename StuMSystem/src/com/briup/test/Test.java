package com.briup.test;

import java.util.Scanner;

import com.briup.bean.Student;
import com.briup.jdbc.StudentDao;

public class Test {
	public static void main(String[] args) {
		StudentDao sd = new StudentDao();
		//sd.checkAll();
		while(true){
			int id;
			String name;
			int age;
			String gender;
			int flg = 0;
			sd.view();
			System.out.println("请选择你需要的操作(1-5)： ");
			Scanner sc = new Scanner (System.in);
			String str = sc.nextLine();
			int num = Integer.parseInt(str);
			switch(num){
			case 1:
				//查看学生信息
				sd.checkAll();
				break;
			case 2:
				//添加
				System.out.println("请按照id，name，age，gender格式录入学生信息");
				System.out.print("请录入学生信息：");
				String line = sc.nextLine();
				String[] arr =line.split(",");
				name =arr[1];
				id =Integer.parseInt(arr[0]) ;
				age =Integer.parseInt(arr[2]);
				gender =arr[3];
				Student s = new Student(id, name, age, gender);
				sd.addStudent(s);
				break;
			case 3:
				//删除
				System.out.println("请输入需要删除的学生学号：");
				id =sc.nextInt();
				sd.deleteStudebtById(id);
				break;
			case 4:
				//修改
		
				System.out.println("请输入要修改的信息（id,name,age,gender格式输入）：");
				line = sc.nextLine();
				String[] arr1 =line.split(",");
				id =Integer.parseInt(arr1[0]);
				name =arr1[1];
				age =Integer.parseInt(arr1[2]);
				gender =arr1[3];
				Student s1 = new Student(id,name, age, gender);
				sd.changeStudentById(id, s1);
					break;
			case 5:
				//退出系统
				flg = 1;
				System.out.println("系统已关闭！");
				break;
			default:
				System.out.println("输入有误！");
				break;
			}
			if(flg == 1)
				break;
		}	
	}
}
