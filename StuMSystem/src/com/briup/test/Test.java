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
			System.out.println("��ѡ������Ҫ�Ĳ���(1-5)�� ");
			Scanner sc = new Scanner (System.in);
			String str = sc.nextLine();
			int num = Integer.parseInt(str);
			switch(num){
			case 1:
				//�鿴ѧ����Ϣ
				sd.checkAll();
				break;
			case 2:
				//���
				System.out.println("�밴��id��name��age��gender��ʽ¼��ѧ����Ϣ");
				System.out.print("��¼��ѧ����Ϣ��");
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
				//ɾ��
				System.out.println("��������Ҫɾ����ѧ��ѧ�ţ�");
				id =sc.nextInt();
				sd.deleteStudebtById(id);
				break;
			case 4:
				//�޸�
		
				System.out.println("������Ҫ�޸ĵ���Ϣ��id,name,age,gender��ʽ���룩��");
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
				//�˳�ϵͳ
				flg = 1;
				System.out.println("ϵͳ�ѹرգ�");
				break;
			default:
				System.out.println("��������");
				break;
			}
			if(flg == 1)
				break;
		}	
	}
}
