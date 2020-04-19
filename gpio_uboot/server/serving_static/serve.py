# serve.py

import os
from flask import Flask, request, abort, jsonify, send_from_directory, render_template
from flask_httpauth import HTTPBasicAuth
from werkzeug.security import generate_password_hash, check_password_hash

UPLOAD_DIRECTORY = "./static/upload"

if not os.path.exists(UPLOAD_DIRECTORY):
    os.makedirs(UPLOAD_DIRECTORY)

users = {
    "user": generate_password_hash("user"),
    "admin": generate_password_hash("admin")
}

auth = HTTPBasicAuth()
app = Flask(__name__)

@auth.verify_password
def verify_password(username, password):
    if username in users:
        return check_password_hash(users.get(username), password)
    return False

@app.route("/files")
def list_files():
    """Endpoint to list files on the server."""
    files = []
    for filename in os.listdir(UPLOAD_DIRECTORY):
        path = os.path.join(UPLOAD_DIRECTORY, filename)
        if os.path.isfile(path):
            files.append(filename)
    return jsonify(files)

@app.route("/files/<path:path>")
def get_file(path):
    """Download a file."""
    return send_from_directory(UPLOAD_DIRECTORY, path, as_attachment=True)

@app.route("/files/<filename>", methods=["POST"])
@auth.login_required
def post_file(filename):
    """Upload a file."""

    if "/" in filename:
        # Return 400 BAD REQUEST
        abort(400, "no subdirectories directories allowed")

    with open(os.path.join(UPLOAD_DIRECTORY, filename), "wb") as fp:
        fp.write(request.data)

    # Return 201 CREATED
    return "", 201

# a route where we will display a welcome message via an HTML template
@app.route("/")
def hello():
    message = "Pawel Grabowski Flask File Server"
    return render_template('index.html', message=message)

# run the application
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=False)
