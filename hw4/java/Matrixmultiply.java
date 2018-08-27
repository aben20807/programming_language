package com.example.bot.spring.echo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;
import java.util.Arrays;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import com.opencsv.CSVWriter;

public class Matrixmultiply {

	private static int[][] am = new int[10][10];
	private static int[][] bm = new int[10][10];
	private static int[][] cm = new int[300][300];
	private static int[][] rm = new int[10][10];

	private static int n = 100;

	private static int[][] a = { { 1, 2, 3, 4 }, { 4, 5, 6, 7 }, { 7, 8, 9, 10 }, { 10, 11, 12, 13 } };
	private static int[][] b = { { 1, 2, 3, 4 }, { 4, 5, 6, 7 }, { 7, 8, 9, 10 }, { 10, 11, 12, 13 } };
	private static int[][] r = new int[4][4];
	private static int[][] c = new int[4][4];
	private static int threadcount = 4;
	private static int[][] a11 = new int[am.length / 2][am.length / 2];
	private static int[][] a12 = new int[am.length / 2][am.length / 2];
	private static int[][] a21 = new int[am.length / 2][am.length / 2];
	private static int[][] a22 = new int[am.length / 2][am.length / 2];
	private static int[][] b11 = new int[am.length / 2][am.length / 2];
	private static int[][] b21 = new int[am.length / 2][am.length / 2];
	private static int[][] b12 = new int[am.length / 2][am.length / 2];
	private static int[][] b22 = new int[am.length / 2][am.length / 2];

	private static long[] time;

	private static boolean[] flag = { true, true, true, true };

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		for (int i = 0; i < am.length; i++) {
			for (int j = 0; j < am.length; j++) {
				am[i][j] = 72;
				bm[i][j] = 72;
			}
		}

		for (int i = 0; i < am.length; i++) {
			for (int j = 0; j < am.length; j++) {
				for (int k = 0; k < am.length; k++) {
					cm[i][j] += am[i][k] * bm[k][j];
				}
			}
		}
		
		BufferedReader br = null;
		FileReader fr = null;
		
		try {
			//br = new BufferedReader(new FileReader(FILENAME));
			fr = new FileReader("/Users/hezhongmiao/Documents/test1");
			br = new BufferedReader(fr);

			String sCurrentLine;

			while ((sCurrentLine = br.readLine()) != null) {
				System.out.println(sCurrentLine);
			}

		} catch (IOException e) {

			e.printStackTrace();

		} finally {

			try {

				if (br != null)
					br.close();

				if (fr != null)
					fr.close();

			} catch (IOException ex) {

				ex.printStackTrace();

			}

		}

	//	o9();
		/*
		 * ass(); assm(); printMatrix(mul(a.clone(),b.clone()));
		 * printMatrix(add(sub(add(m1,m4),m5),m7)); printMatrix(add(m3,m5));
		 * printMatrix(add(m2,m4)); printMatrix(add(add(sub(m1,m2),m3),m6));
		 */
		System.out.println("===================================================================");

		// o3();
	}

	public static class Mul_t extends Thread {
		private int id;

		public Mul_t(int id) {
			this.id = id;
		}

		public void run() {
			o4_run(id);
		}
	}

	private static void s_run(int id) {
		int[][] m1 = new int[am.length / 2][am.length / 2];
		int[][] m2 = new int[am.length / 2][am.length / 2];
		int[][] m3 = new int[am.length / 2][am.length / 2];
		int[][] m4 = new int[am.length / 2][am.length / 2];
		int[][] m5 = new int[am.length / 2][am.length / 2];
		int[][] m6 = new int[am.length / 2][am.length / 2];
		int[][] m7 = new int[am.length / 2][am.length / 2];
		int[][] c1 = new int[am.length / 2][am.length / 2];
		int[][] c2 = new int[am.length / 2][am.length / 2];
		int[][] c3 = new int[am.length / 2][am.length / 2];
		int[][] c4 = new int[am.length / 2][am.length / 2];

		long startTimek = System.currentTimeMillis(); // 程序开始记录时间

		m1 = mul(add(a11, a22), add(b11, b22), id);
		m2 = mul(add(a21, a22), b11, id);
		m3 = mul(a11, sub(b12, b22), id);
		m4 = mul(a22, sub(b21, b11), id);
		m5 = mul(add(a11, a12), b22, id);
		m6 = mul(sub(a21, a11), add(b11, b12), id);
		m7 = mul(sub(a12, a22), add(b21, b22), id);

		flag[id] = false;
		while (flag[0] && flag[1]) {
			System.out.println();
		}
		flag[id] = true;

		c1 = add(sub(add(m1, m4), m5), m7);
		c2 = add(m3, m5);
		c3 = add(m2, m4);
		c4 = add(add(sub(m1, m2), m3), m6);

		flag[id] = false;
		while (flag[0] && flag[1]) {
			System.out.println();
		}

		if (id == 0) {
			for (int i = 0; i < am.length / 2; i++) {
				for (int j = 0; j < am.length / 2; j++) {
					rm[i][j] = c1[i][j];
					rm[i][j + am.length / 2] = c2[i][j];
					rm[i + am.length / 2][j] = c3[i][j];
					rm[i + am.length / 2][j + am.length / 2] = c4[i][j];

				}
			}
		}

		long endTime = System.currentTimeMillis(); // 程序结束记录时间
		long TotalTime = endTime - startTimek; // 总消耗时间
		time[id] = TotalTime;
		System.out.println(TotalTime);
		System.out.println();
	}

	private static void o9() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out9.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int q = 10; q <= 300; q += 10) {
			String[] ns = new String[100];

			am = new int[q][q];
			bm = new int[q][q];
			rm = new int[q][q];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}

			for (int m = 0; m < n; m++) {
				Mul_t[] mul_array = new Mul_t[threadcount];
				time = new long[threadcount];
				for (int i = 0; i < threadcount; i++) {
					mul_array[i] = new Mul_t(i);
					mul_array[i].start();
					try {
						mul_array[i].join();
					} catch (InterruptedException e) {
						System.out.println("error");
					}
				}
				ns[m] = String.valueOf(Arrays.stream(time).max().getAsLong()); // 总消耗时间
			}
			csvWriter.writeNext(ns);
		}

		csvWriter.close();
	}

	private static void o8() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out8.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int q = 10; q <= 300; q += 10) {
			String[] ns = new String[100];

			am = new int[q][q];
			bm = new int[q][q];
			rm = new int[q][q];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}

			for (int m = 0; m < n; m++) {
				Mul_t[] mul_array = new Mul_t[threadcount];
				time = new long[threadcount];
				for (int i = 0; i < threadcount; i++) {
					mul_array[i] = new Mul_t(i);
					mul_array[i].start();
					try {
						mul_array[i].join();
					} catch (InterruptedException e) {
						System.out.println("error");
					}
				}
				ns[m] = String.valueOf(Arrays.stream(time).max().getAsLong()); // 总消耗时间
			}
			csvWriter.writeNext(ns);
		}

		csvWriter.close();
	}

	private static void o4_run(int id) {

		long startTimek = System.currentTimeMillis(); // 程序开始记录时间
		for (int i = id * am.length / threadcount; i < (id + 1) * am.length / threadcount; i++) {
			for (int j = 0; j < am.length; j++) {
				rm[i][j] = 0;
				for (int k = 0; k < am.length; k++) {
					rm[i][j] += am[i][k] * bm[j][k];
				}
			}
		}
		long endTime = System.currentTimeMillis(); // 程序结束记录时间
		long TotalTime = endTime - startTimek; // 总消耗时间
		time[id] = TotalTime;
		System.out.println(TotalTime);
		System.out.println();
	}

	private static void o7() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out7.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int k1 = 10; k1 <= 300; k1 += 10) {
			String[] ns = new String[100];

			int[][] am = new int[k1][k1];
			int[][] bm = new int[k1][k1];
			int[][] rm = new int[k1][k1];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}

			for (int m = 0; m < n; m++) {
				long startTime = System.currentTimeMillis(); // 程序开始记录时间
				for (int i = 0; i < am.length; i++) {
					for (int j = 0; j < am.length; j++) {
						for (int k = 0; k < am.length; k++) {
							rm[i][j] += am[i][k] * bm[j][k];
						}
					}
				}
				long endTime = System.currentTimeMillis(); // 程序结束记录时间
				ns[m] = String.valueOf(endTime - startTime); // 总消耗时间
				System.out.println(ns[m]);
			}

			csvWriter.writeNext(ns);
		}

		csvWriter.close();
	}

	private static void o6() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out6.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int q = 10; q <= 300; q += 10) {
			String[] ns = new String[100];

			am = new int[q][q];
			bm = new int[q][q];
			rm = new int[q][q];
			
			a11 = new int[am.length / 2][am.length / 2];
			a12 = new int[am.length / 2][am.length / 2];
			a21 = new int[am.length / 2][am.length / 2];
			a22 = new int[am.length / 2][am.length / 2];
			b11 = new int[am.length / 2][am.length / 2];
			b21 = new int[am.length / 2][am.length / 2];
			b12 = new int[am.length / 2][am.length / 2];
			b22 = new int[am.length / 2][am.length / 2];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}
			
			ass();
			
			for (int m = 0; m < n; m++) {
				Mul_t[] mul_array = new Mul_t[threadcount];
				time = new long[threadcount];
				for (int i = 0; i < threadcount; i++) {
					mul_array[i] = new Mul_t(i);
					mul_array[i].start();
					try {
						mul_array[i].join();
					} catch (InterruptedException e) {
						System.out.println("error");
					}
				}
				ns[m] = String.valueOf(Arrays.stream(time).max().getAsLong()); // 总消耗时间
			}
			csvWriter.writeNext(ns);
		}
		csvWriter.close();
	}

	private static void o5() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out5.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int q = 10; q <= 300; q += 10) {
			String[] ns = new String[100];

			am = new int[q][q];
			bm = new int[q][q];
			rm = new int[q][q];
			
			a11 = new int[am.length / 2][am.length / 2];
			a12 = new int[am.length / 2][am.length / 2];
			a21 = new int[am.length / 2][am.length / 2];
			a22 = new int[am.length / 2][am.length / 2];
			b11 = new int[am.length / 2][am.length / 2];
			b21 = new int[am.length / 2][am.length / 2];
			b12 = new int[am.length / 2][am.length / 2];
			b22 = new int[am.length / 2][am.length / 2];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}
			
			ass();
			
			for (int m = 0; m < n; m++) {
				Mul_t[] mul_array = new Mul_t[threadcount];
				time = new long[threadcount];
				for (int i = 0; i < threadcount; i++) {
					mul_array[i] = new Mul_t(i);
					mul_array[i].start();
					try {
						mul_array[i].join();
					} catch (InterruptedException e) {
						System.out.println("error");
					}
				}
				ns[m] = String.valueOf(Arrays.stream(time).max().getAsLong()); // 总消耗时间
			}
			csvWriter.writeNext(ns);
		}
		csvWriter.close();
	}

	private static void o4() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out4.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int q = 10; q <= 300; q += 10) {
			String[] ns = new String[100];

			am = new int[q][q];
			bm = new int[q][q];
			rm = new int[q][q];
			
			a11 = new int[am.length / 2][am.length / 2];
			a12 = new int[am.length / 2][am.length / 2];
			a21 = new int[am.length / 2][am.length / 2];
			a22 = new int[am.length / 2][am.length / 2];
			b11 = new int[am.length / 2][am.length / 2];
			b21 = new int[am.length / 2][am.length / 2];
			b12 = new int[am.length / 2][am.length / 2];
			b22 = new int[am.length / 2][am.length / 2];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}
			
			ass();
			
			for (int m = 0; m < n; m++) {
				Mul_t[] mul_array = new Mul_t[threadcount];
				time = new long[threadcount];
				for (int i = 0; i < threadcount; i++) {
					mul_array[i] = new Mul_t(i);
					mul_array[i].start();
					try {
						mul_array[i].join();
					} catch (InterruptedException e) {
						System.out.println("error");
					}
				}
				ns[m] = String.valueOf(Arrays.stream(time).max().getAsLong()); // 总消耗时间
			}
			csvWriter.writeNext(ns);
		}
		csvWriter.close();
	}
	

	private static void o3_run(int id) {

		long startTimek = System.currentTimeMillis(); // 程序开始记录时间
		for (int i = id * am.length / threadcount; i < (id + 1) * am.length / threadcount; i++) {
			for (int j = 0; j < am.length; j++) {
				rm[i][j] = 0;
				for (int k = 0; k < am.length; k++) {
					rm[i][j] += am[i][k] * bm[k][j];
				}
			}
		}
		long endTime = System.currentTimeMillis(); // 程序结束记录时间
		long TotalTime = endTime - startTimek; // 总消耗时间
		time[id] = TotalTime;
		System.out.println(TotalTime);
		System.out.println();
	}

	private static void o3() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out3.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int q = 10; q <= 300; q += 10) {
			String[] ns = new String[100];

			am = new int[q][q];
			bm = new int[q][q];
			rm = new int[q][q];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}
			
			for (int m = 0; m < n; m++) {
				Mul_t[] mul_array = new Mul_t[threadcount];
				time = new long[threadcount];
				for (int i = 0; i < threadcount; i++) {
					mul_array[i] = new Mul_t(i);
					mul_array[i].start();
					try {
						mul_array[i].join();
					} catch (InterruptedException e) {
						System.out.println("error");
					}
				}
				ns[m] = String.valueOf(Arrays.stream(time).max().getAsLong()); // 总消耗时间
			}
			csvWriter.writeNext(ns);
		}

		csvWriter.close();
	}

	private static void o2() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out2.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int q = 10; q <= 300; q += 10) {
			String[] ns = new String[100];

			am = new int[q][q];
			bm = new int[q][q];
			rm = new int[q][q];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}

			for (int m = 0; m < n; m++) {
				Mul_t[] mul_array = new Mul_t[threadcount];
				time = new long[threadcount];
				for (int i = 0; i < threadcount; i++) {
					mul_array[i] = new Mul_t(i);
					mul_array[i].start();
					try {
						mul_array[i].join();
					} catch (InterruptedException e) {
						System.out.println("error");
					}
				}
				ns[m] = String.valueOf(Arrays.stream(time).max().getAsLong()); // 总消耗时间
			}
			csvWriter.writeNext(ns);
		}

		csvWriter.close();
	}

	private static void o1() throws IOException {
		File file = new File("/Users/hezhongmiao/Documents/out1.csv");
		Writer writer = new FileWriter(file);
		@SuppressWarnings("deprecation")
		CSVWriter csvWriter = new CSVWriter(writer, ',');

		for (int k1 = 10; k1 <= 300; k1 += 10) {
			String[] ns = new String[100];

			int[][] am = new int[k1][k1];
			int[][] bm = new int[k1][k1];
			int[][] rm = new int[k1][k1];

			for (int i = 0; i < am.length; i++) {
				for (int j = 0; j < am.length; j++) {
					am[i][j] = 72;
					bm[i][j] = 72;
				}
			}

			for (int m = 0; m < n; m++) {
				long startTime = System.currentTimeMillis(); // 程序开始记录时间
				for (int i = 0; i < am.length; i++) {
					for (int j = 0; j < am.length; j++) {
						for (int k = 0; k < am.length; k++) {
							rm[i][j] += am[i][k] * bm[k][j];
						}
					}
				}
				long endTime = System.currentTimeMillis(); // 程序结束记录时间
				ns[m] = String.valueOf(endTime - startTime); // 总消耗时间
				System.out.println(ns[m]);
			}

			csvWriter.writeNext(ns);
		}

		csvWriter.close();
	}

	private static int[][] add(int[][] a, int[][] b) {
		int[][] c = new int[a.length][a.length];
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a.length; j++) {
				c[i][j] = a[i][j] + b[i][j];
			}
		}
		return c;
	}

	private static int[][] sub(int[][] a, int[][] b) {
		int[][] c = new int[a.length][a.length];
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a.length; j++) {
				c[i][j] = a[i][j] - b[i][j];
			}
		}
		return c;
	}

	private static int[][] mul(int[][] a, int[][] b, int id) {
		int[][] c = new int[a.length][a.length];
		for (int i = id * a.length / threadcount; i < (id + 1) * a.length / threadcount; i++) {
			for (int j = 0; j < a.length; j++) {
				for (int k = 0; k < a.length; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}

		return c;
	}

	private static void printMatrix(int[][] a) {
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a.length; j++) {
				System.out.print(a[i][j]);
				System.out.print(",\t");
			}
			System.out.println();
		}
	}

	/*
	 * private static void assm() { m1 = mul(add(a11, a22), add(b11, b22)); m2 =
	 * mul(add(a21, a22), b11); m3 = mul(a11, sub(b12, b22)); m4 = mul(a22, sub(b21,
	 * b11)); m5 = mul(add(a11, a12), b22); m6 = mul(sub(a21, a11), add(b11, b12));
	 * m7 = mul(sub(a12, a22), add(b21, b22));
	 * 
	 * }
	 */
	private static void ass() {
		for (int i = 0; i < am.length / 2; i++) {
			for (int j = 0; j < am.length / 2; j++) {
				a11[i][j] = am[i][j];
				a21[i][j] = am[i + am.length / 2][j];
				a12[i][j] = am[i][j + am.length / 2];
				a22[i][j] = am[i + am.length / 2][j + am.length / 2];
				b11[i][j] = bm[i][j];
				b21[i][j] = bm[i + am.length / 2][j];
				b12[i][j] = bm[i][j + am.length / 2];
				b22[i][j] = bm[i + am.length / 2][j + am.length / 2];
			}
		}
	}

}
