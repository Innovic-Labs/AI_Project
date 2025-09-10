import requests
import json

# -------------------------------
# CONFIGURATION
# -------------------------------
GITHUB_TOKEN = "YOUR_GITHUB_PAT"   # GitHub Personal Access Token
REPO_OWNER = "octocat"             # Replace with your repo owner
REPO_NAME = "hello-world"          # Replace with your repo name
PR_NUMBER = 1                      # Replace with target PR number

OLLAMA_API_URL = "http://localhost:11434/api/generate"
OLLAMA_MODEL = "llama3.2"

headers = {
    "Authorization": f"Bearer {GITHUB_TOKEN}",
    "Accept": "application/vnd.github+json"
}

# -------------------------------
# STEP 1: Get PR details
# -------------------------------
def get_pr_details():
    url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/pulls/{PR_NUMBER}"
    r = requests.get(url, headers=headers)
    r.raise_for_status()
    return r.json()

# -------------------------------
# STEP 2: Get PR commits
# -------------------------------
def get_pr_commits():
    url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/pulls/{PR_NUMBER}/commits"
    r = requests.get(url, headers=headers)
    r.raise_for_status()
    return r.json()

# -------------------------------
# STEP 3: Get PR files
# -------------------------------
def get_pr_files():
    url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/pulls/{PR_NUMBER}/files"
    r = requests.get(url, headers=headers)
    r.raise_for_status()
    return r.json()

# -------------------------------
# STEP 4: Generate PR Description with LLM
# -------------------------------
def generate_pr_description(pr, commits, files):
    commit_messages = "\n".join([c["commit"]["message"] for c in commits])
    changed_files = "\n".join([f["filename"] for f in files])

    prompt = f"""
    You are an assistant that writes clear Pull Request descriptions.

    PR Title: {pr['title']}
    Commits:
    {commit_messages}

    Changed Files:
    {changed_files}

    Write a standardized, meaningful PR description with:
    - Summary of changes
    - Motivation/Context
    - Risks (if any)
    - Testing/Validation steps
    """

    payload = {
        "model": OLLAMA_MODEL,
        "prompt": prompt
    }

    r = requests.post(OLLAMA_API_URL, json=payload, stream=False)
    r.raise_for_status()
    return r.json()["response"]

# -------------------------------
# STEP 5: Update PR description
# -------------------------------
def update_pr_description(new_body):
    url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/pulls/{PR_NUMBER}"
    data = {"body": new_body}
    r = requests.patch(url, headers=headers, json=data)
    r.raise_for_status()
    return r.json()

# -------------------------------
# MAIN FLOW
# -------------------------------
if __name__ == "__main__":
    pr = get_pr_details()
    commits = get_pr_commits()
    files = get_pr_files()

    print("Generating PR description using Llama3.2...")
    description = generate_pr_description(pr, commits, files)
    print("\nGenerated Description:\n", description)

    print("\nUpdating PR on GitHub...")
    result = update_pr_description(description)
    print("✅ PR updated successfully:", result["html_url"])
