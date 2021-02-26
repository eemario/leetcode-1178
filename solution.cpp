#define n words.size()
#define m puzzles.size()
#define PUZZLE_LEN 7
#define SUBSET_SZ 64
class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<bitset<26>,int> words_hashtable;
        vector<int> ans(m);
        int i, j, k, p;
        for(i = 0; i < n; i++)
        {
            //处理每一个word得到二进制token
            bitset<26> word_token;
            k = words[i].length();
            for(j = 0; j < k; j++)
            {
                word_token.set(words[i][j]-'a');
            }
            //将可能是谜底的word加入哈希表
            if(word_token.count() <= PUZZLE_LEN)
            {
                if(words_hashtable.count(word_token))
                {
                    words_hashtable[word_token]++;
                }
                else
                {
                    words_hashtable.insert({word_token,1});
                }
            }
        }
        for (i = 0; i < m; i++)
        {
            //处理每一个puzzle得到所有子集
            vector<bitset<26>> puzzle_tokens(SUBSET_SZ);
            for (j = 0; j < SUBSET_SZ; j++)    //首字母
            {
                puzzle_tokens[j].set(puzzles[i][0] - 'a');
            }
            for (k = 1; k < PUZZLE_LEN; k++)
            {
                for (j = 0; j < SUBSET_SZ; j += (1 << k))
                {
                    for (p = 0; p < (1 << (k - 1)); p++)
                    {
                        puzzle_tokens[j + p].set(puzzles[i][k] - 'a');
                    }
                }
            }
            //对子集中的每个元素试图匹配
            for (j = 0; j < SUBSET_SZ; j++)
            {
                if (words_hashtable.count(puzzle_tokens[j]))
                {
                    ans[i] += words_hashtable[puzzle_tokens[j]];
                }
            }
        }
        return ans;
    }
};
