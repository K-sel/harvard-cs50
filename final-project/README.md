# Semantic Search Engine
#### Video Demo: http://youtube.com/watch?v=m2oZXbKqaMI
#### Description:

## Overview

This project is a **semantic search engine** that understands the meaning of queries rather than just matching keywords. For example, searching for "fast car" will also find documents containing "sports automobile" or "high-performance vehicle." This represents a fundamental shift from traditional keyword-based search to AI-powered semantic understanding.

I developed this project as my CS50 final project to learn how modern search engines work and to explore the fascinating world of natural language processing and vector embeddings. The application demonstrates how artificial intelligence can dramatically improve information retrieval by understanding context and meaning rather than relying on exact word matches.

## Why Semantic Search?

Traditional search engines have a significant limitation: they only find exact matches. If your document uses "automobile" but you search for "car," a keyword-based system might miss it entirely. Semantic search solves this by converting text into mathematical vectors that capture *meaning*. Words with similar meanings end up close together in vector space, enabling the system to find conceptually similar content even when the exact words differ.

## Project Structure

The project consists of three main components working together:

### Backend (Python/Flask)
- **`app.py`**: The Flask API server that handles search requests. When a user submits a query, this file encodes it into a vector using Sentence Transformers, searches the FAISS index for similar documents, and retrieves the corresponding text from SQLite. I chose Flask for its simplicity and because it integrates seamlessly with Python's machine learning libraries.

- **`dataset.py`**: Downloads and prepares the dataset for indexing. I configured it to download 1,000 Wikipedia articles from the Hugging Face datasets library, filtering for articles with at least 500 characters to ensure meaningful content. The script saves each article as a separate text file in the `data/` directory. I chose Wikipedia because it provides diverse, high-quality content ideal for demonstrating semantic search capabilities.

- **`indexer.py`**: This is the core indexing script that transforms text documents into searchable vectors. It loads all documents from the `data/` folder, encodes each one using the `all-MiniLM-L6-v2` Sentence Transformer model (which converts text into 384-dimensional vectors), normalizes these vectors for cosine similarity search, creates a FAISS index using IndexFlatIP (Inner Product), and saves both the index and document metadata to disk. I chose IndexFlatIP because it provides exact search results with cosine similarity scoring, which is perfect for understanding how well documents match queries (scores range from 0 to 1, where higher is better).

- **`environment.yml`**: Conda environment specification listing all Python dependencies including Flask, FAISS, Sentence Transformers, and PyTorch. I chose Conda over pip because it handles complex dependencies like FAISS more reliably, especially when working with CPU-optimized versions.

- **`Dockerfile`**: Containerizes the backend using Miniconda as the base image, installs dependencies from environment.yml, and runs the Flask server. Docker ensures consistent deployment across different systems.

### Frontend (Vue.js)
- **`src/App.vue`**: The main application component that orchestrates the search interface. It manages the application state (search results and selected documents), fetches index metadata on mount, handles search queries by calling the backend API, and passes data to child components. I structured it to separate concerns clearly, making the code maintainable and easy to understand.

- **`src/component/Header.vue`**: Displays the application title and description. A simple component that provides branding and context for users.

- **`src/component/SearchBar.vue`**: The search input component that accepts user queries and displays the number of indexed documents. It emits search events to the parent component when users submit queries. I added the indexed document count to give users transparency about the dataset size.

- **`src/component/Text-Card.vue`**: Displays individual search results with title, snippet, and similarity score. Each card shows the first 200 characters of the document and visualizes the similarity score as both a percentage and the raw cosine similarity value. The visual design uses gradients to make high-quality matches stand out.

- **`src/component/Text.vue`**: Shows the full content of a selected document in a scrollable panel. When no document is selected, it displays project information explaining how semantic search works. This component provides users with detailed context and educational content about the technology.

- **`vite.config.js`**: Configures the Vite development server with a proxy that routes `/api` requests to the Flask backend. This solves CORS issues during development and maintains a clean separation between frontend and backend.

### Infrastructure
- **`docker-compose.yml`**: Orchestrates both backend and frontend containers, sets up networking between them, and configures port mappings. Using Docker Compose simplifies deployment and ensures the entire stack works together seamlessly.

## How It Works

### The Problem with Traditional Search
Traditional search engines perform **keyword matching**: they look for documents containing exactly the words you typed. This approach has serious limitations:
- Searching for "machine learning" won't find "artificial intelligence" or "deep learning"
- Different languages require separate searches
- Synonyms and paraphrases are treated as completely different concepts

### The Solution: Vector Embeddings
Instead of comparing words, semantic search compares **mathematical vectors** that represent meaning. Here's how it works:

1. **Encoding**: A neural network (Sentence Transformer) converts text into a 384-dimensional vector. Similar concepts produce similar vectors, regardless of the exact words used.

2. **Indexing**: All document vectors are stored in a FAISS index optimized for fast similarity search. FAISS can search millions of vectors in milliseconds.

3. **Search**: When you submit a query, it gets encoded into a vector, FAISS finds the most similar document vectors using cosine similarity, and the results are ranked by similarity score.

The beauty of this approach is that "machine learning" and "apprentissage automatique" (French for machine learning) produce similar vectors even though they share no words in common. The model learned semantic relationships from millions of text examples during training.

## Design Decisions

### Why IndexFlatIP?
I chose `IndexFlatIP` (Inner Product with normalized vectors) over other FAISS index types for several reasons:
- It provides **exact** search results with 100% recall
- Cosine similarity scores (0-1 range) are intuitive: higher scores mean better matches
- The dataset size (~1,000 documents) doesn't require approximate methods
- It's perfect for understanding how semantic search works without complexity

For larger datasets (>100K documents), I would recommend IndexIVFFlat or HNSW for faster approximate search.

### Why all-MiniLM-L6-v2?
This Sentence Transformer model offers an excellent balance:
- **Small size**: Only 80MB, making it fast to download and deploy
- **Good quality**: Trained on over 1 billion sentence pairs
- **Fast encoding**: ~14,000 sentences per second on CPU
- **384 dimensions**: Compact vectors that capture semantic meaning effectively

### Frontend Architecture
I chose Vue.js 3 with the Composition API because:
- Component-based architecture makes code reusable and maintainable
- Reactive state management simplifies UI updates
- Single File Components (.vue files) keep template, logic, and styles together
- It's lightweight compared to frameworks like Angular

Tailwind CSS provides utility-first styling that made it easy to create a modern, responsive interface quickly without writing custom CSS.

## Technical Implementation

### The FAISS Pipeline
1. **Create index**: `faiss.IndexFlatIP(384)` creates an index for 384-dimensional vectors using inner product search
2. **Normalize vectors**: `faiss.normalize_L2(embeddings)` ensures vectors have unit length for cosine similarity
3. **Add vectors**: `index.add(embeddings)` populates the index with document vectors
4. **Search**: `index.search(query_vector, k=5)` finds the 5 most similar documents

### API Design
The backend exposes two endpoints:
- `GET /`: Returns index metadata (number of documents, vector dimensions)
- `GET /search?q=query`: Performs semantic search and returns top 5 results with scores

I kept the API simple and RESTful for easy integration with any frontend.

## Running the Project

### Prerequisites
- Docker and Docker Compose installed
- At least 4GB of available RAM
- Internet connection for downloading the model and dataset

### Setup Instructions

ATTENTION ! To run my code, you need to have docker running on your machine

First, unzip the code.zip file.

1. **Enter the project folder** :
```bash
cd code
```

2. **Launch with Docker**:
```bash
docker-compose up --build
```

3. **Access the application**:
- Frontend: http://localhost:5173
- Backend API: http://localhost:5000

## Challenges and Learning

The most challenging aspect was understanding vector embeddings and FAISS. The documentation assumes familiarity with information retrieval concepts that I had to learn from scratch. I spent considerable time experimenting with different index types and similarity metrics before settling on IndexFlatIP with cosine similarity.

I also learned about the importance of data preprocessing. My first attempts included very short Wikipedia articles that produced poor search results. Adding a minimum length filter dramatically improved result quality.

On the frontend, managing state between components required careful planning. I initially put too much logic in `App.vue` before refactoring into smaller, focused components.

## Future Enhancements

If I continue this project, I would add:
- **Multilingual search**: Use a multilingual model to search across languages
- **Query expansion**: Automatically suggest related search terms
- **Relevance feedback**: Let users mark results as relevant to improve future searches
- **Larger dataset**: Scale to millions of documents using IndexIVF
- **Hybrid search**: Combine semantic and keyword search for best results

## Conclusion

This project taught me how modern AI-powered search works from the ground up. I gained hands-on experience with natural language processing, vector databases, full-stack development, and Docker containerization. Most importantly, I learned how to break down a complex system into understandable components and explain technical concepts clearly.

Semantic search represents the future of information retrieval, and building this search engine gave me deep insight into why companies like Google invest heavily in understanding meaning, not just matching keywords.
