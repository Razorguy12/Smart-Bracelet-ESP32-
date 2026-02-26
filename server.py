from fastapi import FastAPI, Request

app = FastAPI()

@app.post("/scan")
async def scan_data(request: Request):
    body = await request.body()
    data = body.decode("utf-8")
    print("Received:", data)
    return {"status": "received", "data": data}
