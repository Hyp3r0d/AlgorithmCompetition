class Solution {
    public boolean isTransformable(String s, String t) {
        int n = s.length();
        Queue<Integer> []pos = new Queue[10];
        Arrays.setAll(pos, e -> new LinkedList<Integer>());
        for(int i = 0; i < n;i ++) {
            pos[s.charAt(i) - '0'].offer(i);
        }
        for(int i = 0 ; i < n;i ++) {
            int digit = t.charAt(i) - '0';
            if(pos[digit].isEmpty())return false;
            for(int j = 0; j < digit;j ++)
                if(!pos[j].isEmpty() && pos[j].peek() < pos[digit].peek()) return false;
            pos[digit].poll();
        }
        return true;
    }

}