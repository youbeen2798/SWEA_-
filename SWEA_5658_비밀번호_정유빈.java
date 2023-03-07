import java.util.List;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;

public class SWEA_5658_비밀번호_정유빈 {

	static int t;
	static int tc;
	static int n;
	static int k;
	static String st;
	static Set<String> stCollections = new HashSet<String>();
	static StringBuilder sb = new StringBuilder();
	
	static void solution() {
		//n을 4로 나눈다.
		
		int one_side_length = st.length() / 4;
		
		for(int rotateNum = 0; rotateNum < st.length(); rotateNum++) {
			String tmpSt;
			int idx = 0;
			for(int i = 0; i < 4; i++) {
				tmpSt = st.substring(idx, idx + one_side_length);
			//	System.out.println("tmpSt: " + tmpSt);
				stCollections.add(tmpSt);
				idx += one_side_length;
			}
			
			String lastCh = st.substring(st.length() -1, st.length());
			st = st.substring(0, st.length() - 1);
			st = lastCh + st;
		}
		
		List<String> stList = new ArrayList<String>(stCollections);
		
		
		Collections.sort(stList, Comparator.reverseOrder());
		
		
		String selectedSt = stList.get(k - 1);
				
		int ans = 0;
		int idx2 = 0;
		for(int i = selectedSt.length() - 1; i >= 0; i--) {
			char c = selectedSt.charAt(i);
			
			if(Character.isDigit(c)) {
				ans += Integer.parseInt(String.valueOf(c)) * Math.pow(16, idx2++);
			}
			else {
				int num = c - 'A' + 10;
				ans += num * Math.pow(16, idx2++);
			}
		}
		sb.append("#").append(" ").append(tc).append(" ").append(ans).append("\n");
	}
	
	static void input() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		t = Integer.parseInt(br.readLine());
		
		for(tc = 1; tc <= t; tc++) {
			StringTokenizer tokenizer = new StringTokenizer(br.readLine());
			
			n = Integer.parseInt(tokenizer.nextToken());
			k = Integer.parseInt(tokenizer.nextToken());
			st = br.readLine();
			solution();
			stCollections.clear();
		}
		System.out.println(sb.toString());

	}
	public static void main(String[] args) throws NumberFormatException, IOException {
		// TODO Auto-generated method stub

		input();
	}

}
