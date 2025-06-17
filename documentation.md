## Data Loading - In Progress
    - Using Word2Vec, load 3M words into a dictionary to store key value pairs
        - Currently using .bin as a .txt file was too large (10 minutes load), but .bin is still rather slow (31 seconds to read all words)
        - Works, but takes upwards of 20 minutes. Need to optimize further
                - Optimize data read
                - Optimize function call